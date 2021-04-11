import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

# %matplotlib inline
#img = cv2.imdecode(np.fromfile(r"/Users/baigk/work/opencv/27/cat.jpg", dtype=np.uint8), -1)
# cv.IMREAD_COLOR cv.IMREAD_GRAYSCALE
img = cv.imread(r"/Users/baigk/work/opencv/27/cat.jpg", cv.IMREAD_GRAYSCALE)
cv.imshow("image", img)
cv.waitKey(0)
cv.destroyAllWindows()

#video
cv.VideoCapture(r"/Users/baigk/work/opencv/27/test.mp4")
while open:
    ret, frame = vc.read()
    if frame is None:
        break;
    if ret == True:
        gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
            cv.imshow("result", gray)
            if cv.waitKey(100) & 0xff == 27:
                break;
vc.release()
cv.destroyAllWindows()


BLUE = [255,0,0]
img1 = cv.imread(r"/Users/baigk/work/opencv/27/cat.jpg")
replicate = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_REPLICATE)
reflect = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_REFLECT)
reflect101 = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_REFLECT_101)
wrap = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_WRAP)
constant= cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_CONSTANT,value=BLUE)
plt.subplot(231),plt.imshow(img1,'gray'),plt.title('ORIGINAL')
plt.subplot(232),plt.imshow(replicate,'gray'),plt.title('REPLICATE')
plt.subplot(233),plt.imshow(reflect,'gray'),plt.title('REFLECT')
plt.subplot(234),plt.imshow(reflect101,'gray'),plt.title('REFLECT_101')
plt.subplot(235),plt.imshow(wrap,'gray'),plt.title('WRAP')
plt.subplot(236),plt.imshow(constant,'gray'),plt.title('CONSTANT')
plt.show()
