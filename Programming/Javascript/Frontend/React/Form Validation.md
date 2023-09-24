```bash
$ npm install react-hook-form @hookform/error-message
```

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
