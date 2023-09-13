```cypher
CREATE (ee:Person {name: 'Emil', from: 'Sweden', kloutScore: 99});
// MATCH: find nodes
MATCH (ee:Person) WHERE ee.name = 'Emil' RETURN ee;
```



