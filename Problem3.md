
### Problem 3

#### Calculate the bits of entropy in LavaRand

When I went back and thought more about this, I realized I hadn't been phrasing my question properly. The thing I was most confused about was how do you define how the data is pulled exactly. 

So, I googled for cloudflare lavalamp and came across this article -- https://blog.cloudflare.com/lavarand-in-production-the-nitty-gritty-technical-details/

This explained that a video feed was what was pulling the data, which made the problem a lot more tractable. 

I wish I had asked for clarification on this part during the interview, because after that I could come up with some ballpark figures for what the answers should be. 

They estimated the answers using this calculation -- 
"Even if we conservatively assume that the camera has a resolution of 100x100 pixels (of course it’s actually much higher) and that an attacker can guess the value of any pixel of that image to within one bit of precision (e.g., they know that a particular pixel has a red value of either 123 or 124, but they aren’t sure which it is), then the total amount of entropy produced by the image is 100x100x3 = 30,000 bits (the x3 is because each pixel comprises three values - a red, a green, and a blue channel)."

If I had not seen this answer, I would probably do something like assume that the camera had a 720p resolution (1280 x 720 pixels) and answer similarly. However, I would perhaps also mention that this is only for one frame of the input, and assuming mJPEG compression format, not every frame would perhaps have the same amount of entropy because there would be parts of the picture that were static (such as the space between the lamps that has the wall) and since every lamp has a certain range of colors, the mJPEG may also be able to store those colors in a more compressed way with reduced variability between frames. Hence, the entropy in each frame would surely be less than 1280 x 720 x 3 due to the way video frames are stored (unless otherwise specified). This is, however, still a large amount of entropy for most practical purposes.


```python

```
