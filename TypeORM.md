
#### Basic CRUD example

```ts
import { Column, Entity, PrimaryColumn } from "typeorm";
import { UserRole } from "./UserRole";
import { webcrypto } from "node:crypto"

@Entity()
export class User {
    @PrimaryColumn("uuid")
    id: string = webcrypto.randomUUID()

    @Column({ unique: true })
    email: string

    @Column()
    password: string

    @Column()
    name: string

    @Column({ enum: UserRole })
    role: UserRole

	// custom constructors are not mandatory.
    public constructor(email: string, password: string, name: string, role: UserRole = UserRole.USER) {
        this.email = email
        this.password = password
        this.name = name
        this.role = role
    }
}
```

**Note**: TypeORM also has a `PrimaryGeneratedColumn` decorator. We can use that instead of `PrimaryColumn` decorator if we don't want to generate an entity's `uuid` in our application (i.e. and rather have the db auto generate it for us).

```ts
export enum UserRole {
    ADMIN = "ADMIN",
    USER = "USER",
}
```

```ts
import { Repository, In } from "typeorm"
import { User } from "../src/entity/User"
import { Paginated } from "./paginated"

export class UserRepository {
    public constructor(
        private readonly userSource: Repository<User>,
    ) {}

    public async all(): Promise<User[]> {
        return this.userSource.find()
    }

    public async listPaginated(take: number, skip: number): Promise<Paginated<User>> {
        const [data, count] = await this.userSource.findAndCount({ skip, take })
        return { data, count }
    }

    public async findById(userId: User["id"]): Promise<User> {
        return this.userSource.findOneBy({ id: userId })
    }

    public async findByEmail(email: string): Promise<User> {
        return this.userSource.findOne({ where: { email } })
    }

    public async create(user: User): Promise<User> {
        try {
            return await this.userSource.save(user)            
        } catch (err) {
            this.handleConstraintViolations(err)
        }
    }

    public async createMany(users: User[]): Promise<User[]> {
        try {
            await this.userSource.insert(users)
        } catch (err) {
            this.handleConstraintViolations(err)
        }

        const ids = users.map(u => u.id)
        return await this.userSource.find({ where: { id: In(ids) } })
    }

    public async update(user: Partial<User>): Promise<User> {
        try {
            await this.userSource.update(user.id, user)
        } catch (err) {
            this.handleConstraintViolations(err)
        }
        return await this.userSource.findOne({ where: { id: user.id }})
    }

    public async remove(userId: User["id"]): Promise<void> {
        await this.userSource.delete(userId)
    }

    private handleConstraintViolations(err: unknown): never {
        if (err instanceof Error) {
            const message = err.message

            // handle email unique constraint.
            if (message.includes("UNIQUE constraint") && message.includes("user.email")) {
                throw new Error(`User with this email already exists")
            }
        }
        throw err
    } 
}
```


---

### Relationships

#### One-to-one (mandatory)
Consider a `User` has one `UserProfile`. `User` must always have a `UserProfile` and it is not optional.

```ts
import { Column, Entity, JoinColumn, OneToOne, PrimaryGeneratedColumn } from "typeorm";
import { UserRole } from "./UserRole";
import { webcrypto } from "node:crypto"
import { UserProfile } from "./UserProfile";

@Entity()
export class User {
  @PrimaryGeneratedColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column({ unique: true })
  email: string

  @Column()
  password: string

  @Column({ enum: UserRole })
  role: UserRole

  @OneToOne(() => UserProfile, (profile) => profile.user, { cascade: true })
  @JoinColumn()
  profile: UserProfile

  public constructor(email: string, password: string, role: UserRole = UserRole.USER) {
    this.email = email
    this.password = password
    this.role = role
  }
}
```

```ts
import { webcrypto } from "node:crypto";
import { Column, Entity, OneToOne, PrimaryColumn } from "typeorm";
import { User } from "./User";

@Entity()
export class UserProfile {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  name: string

  @Column()
  address: string

  @OneToOne(() => User, (user) => user.profile)
  user: User

  constructor(name: string, address: string) {
    this.name = name
    this.address = address
  }
}
```

```ts
const userSource = AppDataSource.getRepository(User)
const user = new User("one@site.com", "asjcbaskjcb")
const profile = new UserProfile("One", "123 Main street")
user.profile = profile

// profile is saved together with the user because cascades are enabled in
// the user entity.
const createdUsers = await userSource.save(user)
```

```ts
const userWithProfile = await userSource.findOne({ 
	where: { id: "<id>" },
	relations: { profile: true }
})
```

**Note**:
- Only one side of the relationship can have cascades enabled. 
- In the above example, `User` table has cascades enabled. This means that we will be able to insert `User` with `UserProfile` in one go.


---

#### One-to-one (optional)

```ts
import { Column, Entity, Index, OneToOne, PrimaryColumn } from "typeorm";
import { webcrypto } from "node:crypto"
import { UserProfile } from "./UserProfile";

@Entity()
export class User {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column({ unique: true })
  @Index()
  email: string

  @Column()
  password: string

  @OneToOne(() => UserProfile, (profile) => profile.user, { cascade: true })
  profile?: UserProfile

  public constructor(email: string, password: string, profile: UserProfile | undefined) {
    this.email = email
    this.password = password
    this.profile = profile
  }

  // hide password field in JSON serialization.
  toJSON() {
    return {
      ...this,
      password: undefined
    }
  }
}
```

```ts
import { webcrypto } from "node:crypto";
import { Column, Entity, JoinColumn, OneToOne, PrimaryGeneratedColumn } from "typeorm";
import { User } from "./User";

@Entity()
export class UserProfile {
  @PrimaryGeneratedColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  name: string

  @Column()
  address: string

  @OneToOne(() => User, (user) => user.profile)
  @JoinColumn()
  user: User

  constructor(name: string, address: string) {
    this.name = name
    this.address = address
  }
}
```

**Note**: In the above examples, the only difference is in where the `@JoinColumn()` decorator is placed. If we need mandatory one-to-one, decorator is placed on the `User` table. If we want optional one-to-one, it will be placed on the `UserProfile` table. This make perfect sense in terms of SQL as well.

```ts
const user = new User("admin@site.com", "scnaskcjback")
const profile = new UserProfile("Admin", "123 Main street")
user.profile = profile

// this works because cascade is added in User entity.
const savedUser = await AppDataSource.manager.save(user)
```

```ts
const savedUser = await AppDataSource.manager.find(User, {
	where: { email: "admin@site.com" },
	relations: { profile: true }
})
```


---

#### One-to-many 

Consider a `Business` can have many branches. We can model it as follows in TypeORM.

```ts
import { Column, Entity, OneToMany, PrimaryColumn } from "typeorm"
import { Branch } from "./Branch"
import { webcrypto } from "node:crypto"

@Entity()
export class Business {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  name: string

  @OneToMany(() => Branch, (branch) => branch.business, { cascade: true })
  branches: Branch[]

  constructor(name: string, branches: Branch[]) {
    this.name = name
    this.branches = branches
  }
}
```

```ts
import { Column, Entity, ManyToOne, PrimaryColumn } from "typeorm";
import { Business } from "./Business";
import { webcrypto } from "node:crypto";

@Entity()
export class Branch {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  name: string

  @Column()
  address: string

  @ManyToOne(() => Business, (business) => business.branches)
  business: Business

  constructor(name: string, address: string) {
    this.name = name
    this.address = address
  }
}
```

```ts
const savedBusiness = await AppDataSource.manager.findOne(Business, {
	where: { id: "<id>" },
	relations: { branches: true },
})
```

```ts
const branchOne = new Branch("Branch 1", "Address 1")
const branchTwo = new Branch("Branch 2", "Address 2")
const business = new Business("Awesome business", [branchOne, branchTwo])

// branches are saved with business because cascades are enabled in 
// the Business entity.
const savedBusiness = await AppDataSource.manager.save(business)
```

```ts
// saving a new branch under existing business.
const savedBusiness = await AppDataSource.manager.findOne(Business, {
	where: { id: "<id>" },
})

const newBranch = new Branch("Brand new branch", "Some random address")
newBranch.business = savedBusiness
const savedNewBranch = await AppDataSource.manager.save(newBranch)
```


---

#### Many-to-many

Consider that a `Lecture` can have many `Student` and `Student` can have many lectures.

```ts
import { webcrypto } from "crypto";
import { Column, Entity, JoinTable, ManyToMany, PrimaryColumn } from "typeorm";
import { Student } from "./Student";

@Entity()
export class Lecture {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  name: string

  @ManyToMany(() => Student, (student) => student.lectures, { cascade: true })
  @JoinTable()
  students: Student[]

  constructor(name: string, students: Student[]) {
    this.name = name
    this.students = students
  }
}
```

```ts
import { webcrypto } from "crypto";
import { Column, Entity, ManyToMany, PrimaryColumn } from "typeorm";
import { Lecture } from "./Lecture";

@Entity()
export class Student {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  name: string

  @Column({ unique: true })
  rollNumber: string

  @ManyToMany(() => Lecture, (lecture) => lecture.students)
  lectures: Lecture[]

  constructor(name: string, rollNumber: string) {
    this.name = name
    this.rollNumber = rollNumber
  }
}
```

```ts
const savedLectures = await AppDataSource.manager.find(Student, ({
	relations: {
		lectures: true
	}
}))

// OR 

const lectureRepo = AppDataSource.getRepository(Lecture)
const savedLectures = await lectureRepo.find(({
	relations: {
		students: true
	}
}))
```

**Note**: Both above styles are valid, use whichever you prefer.

```ts
const studentOne = new Student("Student one", "A-01")
const studentTwo = new Student("Student two", "A-02")    
const studentThree = new Student("Student three", "A-03")    
await AppDataSource.manager.save([studentOne, studentTwo, studentThree])

const lectureOne = new Lecture("Lecture one", [studentOne, studentTwo])
const lectureTwo = new Lecture("Lecture two", [studentOne, studentThree])
await AppDataSource.manager.save([lectureOne, lectureTwo])    
```

```ts
// create new student and enroll in existing lecture.
const savedLecture = await AppDataSource.manager.findOne(Lecture, {
	where: { id: "389963d8-a558-4869-8d06-b6eafdfd71ca" },
})

const newStudent = new Student("New Student", "casbckj")
newStudent.lectures = [savedLecture]
const savedStudent = await AppDataSource.manager.save(newStudent)
```


---

### Self-referencing relations

```ts
import { Column, Entity, JoinColumn, ManyToOne, OneToMany, PrimaryColumn } from "typeorm";
import { Comment } from "./Comment";
import { webcrypto } from "crypto";

@Entity()
export class Post {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  title: string

  @OneToMany(() => Comment, (comment) => comment.post)
  @JoinColumn()
  comments: Comment[]

  constructor(title: string) {
    this.title = title
  }
}
```

```ts
import { Column, Entity, ManyToMany, ManyToOne, OneToMany, PrimaryColumn } from "typeorm";
import { Post } from "./Post";
import { webcrypto } from "crypto";

@Entity()
export class Comment {
  @PrimaryColumn("uuid")
  id: string = webcrypto.randomUUID()

  @Column()
  text: string

  @ManyToOne(() => Post, (post) => post.comments)
  post: Post

  // this column is not mandatory but helpful to have here.
  // it has the same name as parentComment relations auto-generated column.
  @Column({ nullable: true })
  parentCommentId?: string

  @ManyToOne(() => Comment, (comment) => comment.children, { nullable: true })
  parentComment?: Comment

  @OneToMany(() => Comment, (comment) => comment.parentComment)
  children: Comment[]

  constructor(text: string, parentCommentId?: string) {
    this.text = text
    this.parentCommentId = parentCommentId
  }
}
```

```ts
const foundPost = await AppDataSource.manager.findOne(Post, {
	where: { id: "<id>" }
})

const newComment = new Comment("Root comment", undefined)
newComment.post = foundPost

const childComment = new Comment("Child comment", newComment.id)
childComment.post = foundPost
await AppDataSource.manager.save([newComment, childComment])
```