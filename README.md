# Recursive-Descent Calculator in C

A small command-line calculator in C that supports **integer arithmetic with operator precedence** and **parentheses**. Built as a learning project for recursive-descent parsing.

---

## Features

- Addition (`+`), subtraction (`-`), multiplication (`*`), and division (`/`)  
- Parentheses for grouping expressions: `(2 + 3) * 4`  
- Correct operator precedence (`*` / `/` before `+` / `-`)  
- Syntax error detection: reports invalid expressions like `2++3` or `4*/2`  
- Interactive command-line interface  

---

## Example

```code
  > 1 + 2 * 3
  > Result: 7
  > (1 + 2) * 3
  > Result: 9
  > 4 + 5 / 2
  > Result: 6
  > (1 + 2 * (3 + 5 - 1)) - (20 / (2 + 4))
  > Result: 12
  > 1++
  > Error: syntax not valid.
  > q
```
---

## What's missing

Negative numbers or floats are not supported yet.

---
