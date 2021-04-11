import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

BLUE = [255,0,0]
img1 = cv.imread(r"/Users/baigk/work/opencv/27/cat.jpg")
replicate = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_REPLICATE)
reflect = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_REFLECT)
reflect101 = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_REFLECT_101)
wrap = cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_WRAP)
constant= cv.copyMakeBorder(img1,50,50,50,50,cv.BORDER_CONSTANT,value=BLUE)
#plt.subplot(231),plt.imshow(img1,'gray'),plt.title('ORIGINAL')
##plt.subplot(232),plt.imshow(replicate,'gray'),plt.title('REPLICATE')
#plt.subplot(233),plt.imshow(reflect,'gray'),plt.title('REFLECT')
#plt.subplot(234),plt.imshow(reflect101,'gray'),plt.title('REFLECT_101')
#plt.subplot(235),plt.imshow(wrap,'gray'),plt.title('WRAP')
#plt.subplot(236),plt.imshow(constant,'gray'),plt.title('CONSTANT')
#splt.show()
'''
cat = cv.imread(r"/Users/baigk/work/opencv/27/cat.jpg")
dog = cv.imread(r"/Users/baigk/work/opencv/27/dog.jpg")
print(cat.shape)
print(dog.shape)
ndog = cv.resize(dog, (cat.shape[1], cat.shape[0]))
print(cat.shape)
print(dog.shape)
print(ndog.shape)
res = cv.addWeighted(cat, 0.7, ndog, 0,3, 0)
cv.imshow("res", res)
cv.imshow("ndog", ndog)
cv.imshow("cat", cat)
plt.imshow(res)
plt.subplot(231),plt.imshow(res,'gray'),plt.title('ORIGINAL')
cv.waitKey(100000)
cv.destroyAllWindows()


import numpy as np
import matplotlib.pyplot as plt
t=np.arange(0.0,2.0,0.1)
print(t)
s=np.sin(t*np.pi)#2×np.pi就相当于2π
print(s)
# 解决中文显示问题
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

plt.subplot(2,2,1) #要生成两行两列，这是第一个图plt.subplot('行','列','编号')
plt.plot(t,s,'b--')
plt.title('千玺')
plt.ylabel('y1')
plt.subplot(2,2,2) #两行两列,这是第二个图
plt.plot(2*t,s,'r--')
plt.title('郑爽')
plt.ylabel('y2')
plt.subplot(2,2,3)#两行两列,这是第三个图
plt.plot(3*t,s,'m--')
plt.title('周杰伦')
plt.ylabel('y3')
plt.subplot(2,2,4)#两行两列,这是第四个图
plt.plot(4*t,s,'k--')
plt.title('乔丹')
plt.ylabel('y4')


lena = cv.imread(r"/Users/baigk/work/opencv/27/lenaNoise.png", 1)
b,g,r = cv.split(lena)

lena_new = cv.merge((r,g,b))
plt.subplot(2,2,1)
plt.imshow(lena_new)
plt.title("origin")
plt.xticks([]),plt.yticks([])
plt.show()
plt.show()
'''

a1 = cv.imread(r"/Users/baigk/Downloads/1.jpeg", 1)
a2 = cv.imread(r"/Users/baigk/Downloads/2.jpeg", 1)
a3 = cv.imread(r"/Users/baigk/Downloads/3.jpeg", 1)
cv.imshow("1",a1)
cv.imshow("2",a2)
cv.imshow("3",a3)
cv.waitKey(100000)
cv.destroyAllWindows()
