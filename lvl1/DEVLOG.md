# Devlog LVL1

## What I did:
I developed a calculator that runs on bare metal on a raspberry pi pico WH. Uses 64 bit integers to avoid overflow. The code validates the inpput multiple times to make sure it is valid. Identifies negatives when the current value entered is 0 and the user entered "-". Enter automatically enters the name into the calculator sum, checks how big or small is it compared to the previously stored values.

## Bugs I found:

### 1. Empty Enter stored a 0
- **Symptom:** pressing Enter twice with no digits stored two zeros (Size: 2). That ruined the average calculation and the `dataSize` counter.
- **Cause:** on Enter I saved `current` no matter what, and with no digits typed it was still 0. A first attempt compared against `'0'` (the character, worth 48), which rejected the number 48 instead.
- **Fix:** added `if` checks to validate the input: Enter with `current == 0` is rejected with "Please enter a number!". Trade-off: a real 0 can't be entered either.

### 2. Overflow check that could never fire
- **Symptom:** typing a huge number didn't trigger my "exceeds numeric_limits" message.
- **Cause:** I checked `current > numeric_limits<int>::max()` *after* computing `current * 10 + digit`. An `int` can never be bigger than the biggest `int`; by then it had already overflowed and wrapped around. Signed overflow is undefined behavior, so you have to prevent it, not detect it.
- **Fix:** check *before* multiplying, rearranged so only shrinking operations happen: `current > (max - digit) / 10`.

### 3. Sum overflow
- **Symptom:** `2147483647` + `1` gave `Sum is: -2147483648` and a negative average.
- **Cause:** `sum` was an `int`, and adding two valid numbers pushed it past the max, so it wrapped. `unsigned` wouldn't fix it: it still wraps (just later) and can't hold negatives.
- **Fix:** made `sum` an `int64_t`, which has room for the worst-case total.

### 4. Negatives broke the overflow check
- **Symptom:** typing `-1` printed "Number exceeds numeric_limits".
- **Cause:** I made each digit negative as it arrived. The check does `max - digit`, and subtracting a negative is adding, so `max + 1` overflowed inside the check itself.
- **Fix:** build the number as positive, remember the sign in a `bool isNegative`, and flip it on Enter. Reset the flag on every path that discards a number (empty Enter, full, overflow), or the next number comes out negative.

### 5. The array I wasn't using
- **Symptom:** none, found in review. `data[]` was written to but never read.
- **Cause:** I switched to keeping `sum`/`min`/`max` up to date as numbers arrive, so nothing needed the stored values anymore. It also hid a bug: `current` was `int64_t` but `data[]` was `int`, so big numbers would have been silently chopped.
- **Fix:** deleted the array. Don't store what you don't need.


## Experiments:

| Type | Pico | Mac |
|---|---|---|
| `long` | 4 | 8 |
| `void*` | 4 | 8 |
| `dataHolder` (struct) | 48 | 48 |




## What I learned:
I learned why not to use a vector on previous versions of the code, as the vector whenever it expands it copies to double of its size, taking more memory. I ended up using an array of a fixed size. I also experienced an overflow for the first time, this is why instead of a standard 32 bit int, I used 64 bit int to avoid overflow. 


# NEXT: LVL2
