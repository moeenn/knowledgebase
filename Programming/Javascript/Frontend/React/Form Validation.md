```bash
$ npm install react-hook-form @hookform/error-message
```

```tsx
import { FC } from "react"

type Props = {
  message: string
}

export const InputError: FC<Props> = ({ message }) => {
  return (
    <p className="text-xs text-red-700">{message}</p>
  )
}
```


#### Basic example (Not recommended)

```tsx
import { useForm } from "react-hook-form"
import { ErrorMessage } from "@hookform/error-message"
import { InputError } from "@/components/InputError"

type Form = {
  email: string
  password: string
}

const formValidators = {
  email: { required: "Email is required" },
  password: {
    required: "Password is required",
    minLength: {
      value: 8,
      message: "Password must be at least 8 characters"
    }
  }
}

export function LoginForm() {
  const { register, handleSubmit, formState: { errors } } = useForm<Form>()
  const onSubmit = (form: Form) => console.log("submitted", form)

  return (
    <form className="flex flex-col space-y-5" onSubmit={handleSubmit(onSubmit)}>
      <fieldset className="flex flex-col space-y-3">
        <label className="text-sm" htmlFor="email">Email</label>
        <input
          className="px-3 py-2 bg-gray-100"
          type="email" required
          {...register("email", formValidators.email)}
        />
        <ErrorMessage
          errors={errors}
          name="email"
          render={({ message }) => <InputError message={message} />}
        />
      </fieldset>

      <fieldset className="flex flex-col space-y-3">
        <label className="text-sm" htmlFor="password">Password</label>
        <input
          className="px-3 py-2 bg-gray-100"
          type="password" required minLength={8}
          {...register("password", formValidators.password)}
        />
        <ErrorMessage
          errors={errors}
          name="password"
          render={({ message }) => <InputError message={message} />}
        />
      </fieldset>

      <div className="py-4">
        <input
          className="bg-gray-200 hover:bg-gray-300 text-sm px-4 py-2"
          type="submit"
          value="Login"
        />
      </div>
    </form>
  )
}
```


#### Validation with `zod` (Recommended)

**Note**: If we validate the front-end forms with `zod`, we can also use the same schema for request validation on the back-end.

```bash
$ npm i zod @hookform/resolvers @hookform/error-message 
```

```tsx
import { zodResolver } from "@hookform/resolvers/zod"
import { useForm } from "react-hook-form"
import { ValidatedInput } from "./ValidatedInput"
import { LoginFormSchema, LoginFormValues } from "@/lib/formSchemas"

type Props = {
  onSubmit: (form: LoginFormValues) => void
}

export function LoginForm(props: Props) {
  const {
    handleSubmit,
    register,
    formState: { errors }
  } = useForm<LoginFormValues>({
    resolver: zodResolver(LoginFormSchema), // this line is important
    mode: "onBlur",
  })

  return (
    <form onSubmit={handleSubmit(props.onSubmit)} 
    className="flex flex-col space-y-6">
      <ValidatedInput
        type="email"
        label="Email"
        register={register("email")}
        field="email"
        errors={errors}
      />

      <ValidatedInput
        type="password"
        label="Password"
        register={register("password")}
        field="password"
        errors={errors}
      />

      <input
        type="submit"
        value="Login" 
        className="px-3 py-2 text-sm bg-blue-500 text-white rounded shadow-lg shadow-blue-100 outline-blue-500"
      />
    </form>
  )
}
```

**Note**: When working with NextJS, ensure that the form component is a client component.


```tsx
import { ErrorMessage, FieldValuesFromFieldErrors } from "@hookform/error-message"
import { HTMLInputTypeAttribute } from "react"
import { FieldErrors, FieldName, UseFormRegisterReturn } from "react-hook-form"
import { InputError } from "./InputError"

type Props<T extends Record<string, unknown>> = {
  type: HTMLInputTypeAttribute
  label?: string
  register: UseFormRegisterReturn
  field: FieldName<FieldValuesFromFieldErrors<FieldErrors<T>>>
  errors: FieldErrors<T>
}

export function ValidatedInput<T extends Record<string, unknown>>(props: Props<T>) {
  return (
    <fieldset className="flex flex-col space-y-1">
      {props.label &&
        <label htmlFor={props.field} className="text-xs">{props.label}</label>
      }
      <input type={props.type} className="px-3 py-2 text-sm border border-gray-100 rounded bg-gray-50 outline-blue-500" {...props.register} />
      <ErrorMessage
        errors={props.errors}
        name={props.field}
        render={({ message }) => <InputError message={message} />}
      />
    </fieldset>
  )
}
```

```ts
import { z } from "zod"

export const LoginFormSchema = z.object({
  email: z.string().email(),
  password: z.string().min(8)
})

export type LoginFormValues = z.infer<typeof LoginFormSchema>
```

