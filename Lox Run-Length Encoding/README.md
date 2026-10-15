*Instead of one int per byte of code, store one (line, count) pair per run of consecutive instructions that share a source line. The memory cost now scales with the number of line changes, not the number of bytes.*

**chunk.h:**
1. Add LineRun struct which tracks the line and count of bytes of code in the run.
2. Instead of storing lines as int pointer in the Chunk, now we have lineCount and lineCapacity, which are the number of and capacity of runs/line changes, respectively, and the lines are stored as LineRuns
3. Define a getLine() function that determines the line where the instruction occurs.

**chunk.c:**
1. In initChunk(), initialize lineCount and lineCapacity to 0.
2. In freeChunk(), adjust so that we are freeing lines by lineCapacity instead of capacity.
3. In writeChunk(), if we are on same line, just add to the count of the LineRun. Otherwise, start a new LineRun by growing the lines array.
4. Implement getLine(), which looks for the line that the instruction is in based on the instruction's offset value.

**debug.c:**
1. Adjust dissasembleInstruction() to use getLine() to account for structure change.

