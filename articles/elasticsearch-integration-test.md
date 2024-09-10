# Implementing Elasticsearch Integration Test with [jest-search](https://github.com/geek-fun/jest-search)

Elasticsearch has become an integral part of modern applications, especially those dealing with large volumes of data and requiring efficient search capabilities. When developing applications that utilize Elasticsearch, it's crucial to ensure that the integration between your application and Elasticsearch functions correctly. One effective way to achieve this is through integration testing.

## Integration tests

Integration testing involves testing the interaction between different components of an application to ensure they work together as expected. In the context of Elasticsearch, integration testing ensures that your application can properly communicate with the Elasticsearch instance and perform various operations such as indexing documents, searching, and aggregations.

## Setting Up Elasticsearch Integration Testing

There are several ways to implement integration test for Elasticsearch, you can startup a container to run the elasticsearch server or config a remote elasticsearch server that you dedicated for test purpose only. In this post, I will give you a another way to implement Elasticsearch Integration Test by using jest-preset [jest-search](https://github.com/geek-fun/jest-search) to startup a local server for you.

### [jest-search](https://github.com/geek-fun/jest-search)

jest-search is a jest-preset that can helps you startup Elasticsearch, OpenSearch and ZincSearch in your local, it automaticlly download and start the server before your test start and stop the server when test finished.

### Prerequisite:

ElasticSearch and OpenSearch relies on Java, please make sure you have Java installed and `JAVA_HOME` is set.

`jest-search` provide two ways to set up, one is two set up globally, another is running in specific test only

### 1. Installing jest-search

To get started with integration testing using `jest-search`, you need to install the package first. You can do this using npm

```bash
npm install --save-dev @geek-fun/jest-search
```

### 2. config the server

you can find all the configurable items and detailed explaination in the [readme](https://github.com/geek-fun/jest-search)

```javascript
module.exports = () => {
  return {
    engine: 'elasticsearch', // or 'opensearch' or 'zincsearch'
    version: '8.8.2',
    port: 9200,
    binaryLocation: '', // optional
    clusterName: 'jest-search-local',
    nodeName: 'jest-search-local',
    zincAdmin: 'admin',
    zincPassword: 'Complexpass#123',
    indexes: [
      {
        name: 'index-name',
        body: {
          settings: {
            number_of_shards: '1',
            number_of_replicas: '1'
          },
          aliases: {
            'your-alias': {}
          },
          mappings: {
            dynamic: false,
            properties: {
              id: {
                type: 'keyword'
              }
            }
          }
        }
      }
    ]
  };
};
```

### 3. create  `jest-global-setup.js`

```javascript
const { globalSetup } = require('@geek-fun/jest-search');
module.exports = async () => {
  await Promise.all([globalSetup()]);
};
```

### 4. create  `jest-global-teardown.js`

```javascript
const { globalTeardown } = require('@geek-fun/jest-search');
module.exports = async () => {
  await Promise.all([globalTeardown()]);
};
```

### 5. modify the `jest-config.js`

```javascript
module.exports = {
	...
  globalSetup: '<rootDir>/jest-global-setup.js',
  globalTeardown: '<rootDir>/jest-global-teardown.js',
};
```

### 6. play with your tests

```typescript
// tests/utils/helper.ts sample utils to add item for test
export const saveBook = async (bookDoc: { name: string; author: string }) => {
  await esClient.index({ index, body: bookDoc, refresh: true });
};

// tests/book.test.ts sample test
beforeAll(async () => {
  await saveBook(mockBook);
});
```

### specific test only
above steps will startup the server when you `npm run test`, if you only want to start a server when you run a specific file, you can use beforeAll and afterAll to control it. here the steps:
the step 1 and 2 are the same as above, `jest-search` export two methods `startEngine` and `stopEngine` to start and stop the search engine, you can manually call them in your test file, the `startEngine` accepts same argument object as defined in `jest-search-config.js` file
```typescript
import { startEngine, stopEngine } from '@geek-fun/jest-search';
// eslint-disable-next-line @typescript-eslint/ban-ts-comment
// @ts-ignore
import loadConfig from '../jest-search-config.js';


describe('integration test for elasticsearch', () => {
  beforeAll(async () => {
    await startEngine(loadConfig());
    await saveBook(mockBook);
  });
  afterAll(async () => {
    await stopEngine();
  });
  it('should get book when search with valid book name', async () => {
    // ...
  });
});

```

## Running Integration Tests

To run the integration tests, you can use the Jest test runner:

```bash
npm run test
```

## Conclusion

Integration testing is crucial for verifying the interaction between your application and Elasticsearch. With `jest-search`, you can easily write integration tests to ensure that your application behaves correctly when communicating with Elasticsearch/OpenSearch and ZincSearch. 

here is a example repo you can also refer: https://github.com/Blankll/event-search