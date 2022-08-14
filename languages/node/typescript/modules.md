## export import

```js
// export the default export of a legacy (`export =`) module
export import MessageBase = require('./message-base');

// export the default export of a modern (`export default`) module
export { default as MessageBase } from './message-base';

// when '--isolatedModules' flag is provided it requires using 'export type'.
export type { default as MessageBase } from './message-base';

// export an interface from a legacy module
import Types = require('./message-types');
export type IMessage = Types.IMessage;

// export an interface from a modern module
export { IMessage } from './message-types';
```