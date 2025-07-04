# Probabilistic-string-matching

## Overview
This project implements a pattern matching algorithm with time complexity O(m + n) and space complexity O(log m + log n). The algorithm is designed to find all occurrences of a pattern `p` in a document `x` with minimal working memory and controlled false positives.

## Key Features
- **Efficient Time Complexity**: Similar to the Knuth-Morris-Pratt algorithm.
- **Reduced Space Complexity**: Uses O(log m + log n) working memory.
- **Error Control**: Provides a mechanism to limit false positives with a probability `ε`.

## Algorithms Implemented
1. **modPatternMatch(q, p, x)**:
   - Finds occurrences of `p` in `x` using a prime number `q` to reduce space complexity.
2. **randPatternMatch(ε, p, x)**:
   - Chooses a random prime `q` to control false positives and uses `modPatternMatch`.
3. **modPatternMatchWildcard(q, p, x)**:
   - Handles patterns with a single wildcard character.
4. **randPatternMatchWildcard(ε, p, x)**:
   - Uses a random prime `q` and handles patterns with a wildcard.

## Functions to Implement
- **findN(eps, m)**:
  - Computes an appropriate value for `N` based on pattern length `m` and error probability `ε`.
- **modPatternMatch(q, p, x)**:
  - Finds occurrences of `p` in `x` modulo `q`.
- **modPatternMatchWildcard(q, p, x)**:
  - Handles wildcard in pattern `p`.


