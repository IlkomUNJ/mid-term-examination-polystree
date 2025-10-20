PROMPT: 
- https://gemini.google.com/share/835442cd90fb
- I also use Perplexity, but I can't seem to share it as it just loading when I click share.
----

# Objective 1: Analyze and Finding Correct Window Size

## Window Size Comparison
I tested multiple window sizes: 3×3, 5×5, 7×7, 10×10, 20×20, 50×50, and 100×100.

## My findings
- All small window sizes (3×3, 5×5, 7×7) produced identical results
- Majority of window contained only a single activated pixel
- No actual information could be captured

## My conclusion
After thoroughly testing each window sizes, I would say the ideal window size is 10×10, because it provides the optimal trade-off between capturing meaningful line segment information and avoiding meaningless repetitive pattern.

# Objective 2: Report All Fitting of Appropriate Window Pattern

### Valid Segment Pattern Criteria
1. The Edge of a Line

If it captures the start of a thick vertical line on the left side of the window, the pattern would look like this:
```
0 0 0 0 1 1 1
0 0 0 0 1 1 1
0 0 0 0 1 1 1
0 0 0 0 1 1 1
0 0 0 0 1 1 1
0 0 0 0 1 1 1
0 0 0 0 1 1 1
```
2. The Middle of a Line

If the window is fully inside a thick horizontal line, the pattern will be solid.
```
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
```
3. A Corner

If you draw a right-angle corner, the window will capture L-shaped patterns.
```
1 1 1 1 1 0 0
1 1 1 1 1 0 0
1 1 0 0 0 0 0
1 1 0 0 0 0 0
1 1 0 0 0 0 0
1 1 0 0 0 0 0
1 1 0 0 0 0 0
```
4. A Thin or Dotted Line

For very fine details, you might get sparse patterns with only a few 1s.
```
0 0 0 1 0 0 0
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
1 0 0 0 0 0 0
0 0 0 0 0 0 0
```

## My conclusion
Valid segment patterns show contiguous pixel clusters forming line structures. The 10×10 window effectively captures these patterns with minimal repetition.