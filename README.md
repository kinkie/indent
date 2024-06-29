Throw-away experiment of ways to more reliably express
yaml indentation.

Sample output as of commit ddcf046
```
level0.1:
  level1.1:
    a: 1
    b: 2
  level1.2:
    a: 4
    b: 5
level0.2:
  - k1: v1
    k2: v2
  - k1: v1
    k2: v2
**** using Indent()
  level0.1:
    level1.1:
      a: 1
      b: 2
    level1.2:
      a: 4
      b: 5
  level0.2:
  - k1: v1
    k2: v2
  - k1: v1
    k2: v2
**** using Indent() and scopes
  level0.1:
    level1.1:
      a: 1
      b: 2
    level1.2:
      a: 4
      b: 5
  level0.2:
    - k1: v1
      k2: v2
    - k1: v1
      k2: v2
```
