# TypeScript

keep dist folder structure same as source code:

tsconfig.json:

```json
{
  "compilerOptions": {
    ...
    "outDir": "./dist",
    "rootDir": "./"
  },
  "include": ["src/**/*", "tests/**/*"]
}
```

