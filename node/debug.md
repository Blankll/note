# debug

 node inspector开启一个新的进程用于debug

```bash
node --inspect index.js
node --inspect-brk index.js #hold process until debuger connected
```

Inspector clients

- node-inspect

  ```bash
  node inspect localhost:9229
  ```

- Chrome/Edge

  Icon in chrome inspect 

- vscode

- idea

## debug tests

```bash
node --inspect-brk node_modules/.bin/jest --runInBand test/dir/file
node <path-to-jest> -i <you-test-file> -c <jest-config> -t "<test-block-name>"
```

Attach to port

## debug in docker

```bash
docker run -p 9229:9229 -p 3000:3000 -v ${pwd}:/app node_image "--inspect=0.0.0.0:9229" "/app/server.js"
```

attach in vscode

```json
{
  "type": "node",
  "request": "attach",
  "name": "docker attach node",
  "localRoot": "${workspaceFolder}/dir_to_root",
  "remoteRoot": "/app"
  
}
```

Debug by npm

```bash
npm start -- --inspect
```



## run jest test

Run single file or a dir

```bash
npx jest -i path/to/dir/or/file
```

Run single it case

```bash
npx jest -i path/to/dir/or/file -t 'it case str'
```



https://github.com/microsoft/vscode-recipes