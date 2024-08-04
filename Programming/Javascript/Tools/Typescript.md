
```json
{
  "compilerOptions": {
    "target": "es2020",
    "module": "es2020",
    "allowJs": true,
    "removeComments": true,
    "resolveJsonModule": true,
    "typeRoots": ["./node_modules/@types"],
    "sourceMap": true,
    "outDir": "dist",
    "strict": true,
    "alwaysStrict": true,
    "lib": ["es2020"],
    "forceConsistentCasingInFileNames": true,
    "esModuleInterop": true,
    "experimentalDecorators": true,
    "emitDecoratorMetadata": true,
    "moduleResolution": "Node",
    "skipLibCheck": true,
    "strictNullChecks": true,
    "noUncheckedIndexedAccess": true,
    "noImplicitAny": true,
    "noImplicitOverride": true,
    "noPropertyAccessFromIndexSignature": true,
    "exactOptionalPropertyTypes": true,
    "strictPropertyInitialization": true,
    "noImplicitThis": true,
    "strictBindCallApply": true,
    "noImplicitReturns": true,
    "noFallthroughCasesInSwitch": true,
    "allowUnreachableCode": false,
    "strictFunctionTypes": true,
    "isolatedModules": true,
    "baseUrl": "./src",
    "paths": {
      "@/*": ["./*"]
    }
  },
  "include": ["src/**/*"],
  "exclude": ["node_modules", "**/node_modules/**"]
}
```