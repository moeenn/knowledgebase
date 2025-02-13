```ts
import { randomUUID } from "crypto"

class Tag {
  public readonly id: string
  public readonly name: string
  public readonly parentId: string | null 

  constructor(id: string, name: string, parentId: string | null) {
    this.id = id
    this.name = name
    this.parentId = parentId
  }

  public static createWithId(name: string, parentId: string | null) {
    return new Tag(randomUUID(), name, parentId)
  }
} 

class TagWithChildren {
  public readonly tag: Tag
  public readonly children: TagWithChildren[]

  constructor(tag: Tag) {
    this.tag = tag
    this.children = []
  }  

  toJSON() {
    return {
      ...this.tag,
      parentId: undefined,
      children: this.children,
    }
  }
}

function buildTagHierarchy(tags: Tag[]): TagWithChildren[] {
  const tagsWithChildren = tags.map(tag => new TagWithChildren(tag))
  const tagMap = new Map<string, TagWithChildren>()
  tagsWithChildren.forEach(tag => tagMap.set(tag.tag.id, tag))

  const result: TagWithChildren[] = []
  for (const tag of tagsWithChildren) {
    if (!tag.tag.parentId) {
      result.push(tag)
    } else {
      const parent = tagMap.get(tag.tag.parentId)
      if (parent) {
        parent.children.push(tag)
      } else {
        result.push(tag)
      }
    }
  }

  return result
}

function flattenTagHierarchy(tags: TagWithChildren[]): Tag[] {
  const flattened: Tag[] = []

  function traverse(nodes: TagWithChildren[], parentId: string | null = null) {
    for (const node of nodes) { 
      flattened.push(new Tag(node.tag.id, node.tag.name, parentId))
      if (node.children.length > 0) {
        traverse(node.children, node.tag.id)
      }
    }
  }

  traverse(tags)
  return flattened 
}

function main(): void {
  const root = Tag.createWithId("Root", null)
  const levelOne = Tag.createWithId("Level one", root.id)
  const levelTwo = Tag.createWithId("level two", levelOne.id)
  const tags: Tag[] = [root, levelOne, levelTwo]

  const tagHierarchy = buildTagHierarchy(tags)
  const flattened = flattenTagHierarchy(tagHierarchy)
  const encoded = JSON.stringify({ tagHierarchy, flattened })
  console.log(encoded)
}

main()
```