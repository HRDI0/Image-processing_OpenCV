# Mophology

Project Goal : input image의 굵기가 다른 텍스트들을 모두 동일한 최소 굵기로 만들고 주변 그림들을 최대한 제거한다.


### input image :
<img src="/mophology/im.jpg" width="50%" height="50%" title="increase object2" alt="increase object2"></img><br/>

--------------------------------
## Mophology연산 : 
erosion
이미지 주변을 깍아내는 연산. 입력영상이 커널에 1로 채워진 영역과 완전히 겹치지 않으면 해당 픽셀을 0으로 변경한다.

dilatation
erosion과 반대로 이미지를 확장하는 연산. 입력 영상이 커널에 1로 채워진 영역과 완전히 겹치지 않으면 해당 픽셀을 1로 변경한다.

opening = erosion + dilatation
주변보다 밝은 노이즈를 제거하거나 개체를 분리, 돌출된 부분을 제거하는데 효과적.

closing = dilatation + erosion
주변보다 어두은 노이즈를 제거하거나 개체를 연결, 구멍을 메우는데 효과적

gradient = dilatation result - erosion result
dilatation 연산 결과에서 erosion 연산 결과를 빼게 되면 경계부부만 얻게 된다. 이를 gradient라고 한다.

tep hat = input - opening
black hat = closing - input

--------------------------------------

문제점
이미지에 텍스트들이 각각 굵기가 다르기 때문에 한번에 모든 텍스트를 최소 굵기로 만드는 것이 어렵다.

도출한 해결법
비슷한 굵기의 글자들끼리 모아서 연산한후 두 연산 결과를 원본 이미지처럼 합친다.

------------------------------------
### binary input image
<img src="/mophology/result_img/binary.JPG" width="50%" height="50%" title="increase object2" alt="increase object2"></img><br/>


### result 1:
<img src="/mophology/result_img/skel1.JPG" width="50%" height="50%" title="increase object2" alt="increase object2"></img><br/>

### result 2:
<img src="/mophology/result_img/skel2.JPG" width="50%" height="50%" title="increase object2" alt="increase object2"></img><br/>


### result 3:
<img src="/mophology/result_img/skel3.JPG" width="50%" height="50%" title="increase object2" alt="increase object2"></img><br/>

