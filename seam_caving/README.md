__# SeamCaving__

## 개요

<p float="left">
<img src="/seam_caving/image/use image/input.jpg" width="35%" height="35%" title="input image" alt="input image"></img>  --->  
<img src="/seam_caving/image/use image/가로변환.jpg" width="20%" height="20%" title="가로변환" alt="가로변환"></img>
<img src="/seam_caving/image/use image/세로변환.jpg" width="30%" height="30%" title="세로변환" alt="세로변환"></img><br/>
</p>

이미지의 크기를 변환하면 이미지가 왜곡되는 현상 발생   
   
이미지의 왜곡을 해결하기 위해서 이미지에서 중심이 되는 오브젝트를 찾고 해당 오브젝트를 제외하고 이미지의 크기를 변환한다면 
위 이미지처럼 변환했을 때와는 달리 배경만 늘리고 줄일 수 있다.

원리는 다음과 같다.

1. 어떤 픽셀이 주위 픽셀과 얼마나 비슷한지 계산하는 에너지 함수를 정의한다.( E = (x 방향 변화율) + (y 방향 변화율))
2. 에너지 합 E가 가장 작은 픽셀의 너비의 가로줄 혹은 세로줄을 정의한다 (seam Line)
3. 이미지를 가로(세로)로 늘릴 때는 가로(세로) Seam을 복사해서 옆줄에 추가한다. 이미지를 가로(세로)로 줄일 때는 가로(세로) Seam을 삭제한다.
4. 원하는 이미지 크기가 될때까지 반복한다.

알고리즘은 적용한 결과는 다음과 같다.

<p float="left">
<img src="/seam_caving/image/use image/input.jpg" width="35%" height="35%" title="input image" alt="input image"></img>  --->  
<img src="/seam_caving/image/use image/seamcarving decrease.JPG" width="30%" height="30%" title="decrease" alt="decrease"></img>
<img src="/seam_caving/image/use image/seamcarving increase.JPG" width="30%" height="30%" title="increase" alt="increase"></img><br/>
</p>

왼쪽의 input image 를 가로로 줄인 결과물과 가로로 늘린 결과물이다. 일반적으로 이미지를 늘리거나 줄였을 때 이미지가 왜곡되는 현상이 해소된것을 볼 수 있다.

---------------------------------------------------------------------

## 문제점

하지만 이미지를 늘리고 줄일 때 문제가 몇가지 있다.
먼저 최소 에너지 픽셀(E)를 단순히 최소인 경우만 뽑아서 삭제, 추가 시키면 Y축에서 E 픽셀은 X좌표가 각각 다르기 때문에 이미지 자체가 일그러져 버리는 경우가 있다.
이는 E 픽셀을 찾은 후 Back Traking으로 한줄의 seam을 만드는 것으로 알고리즘에서 해결이 된다.

그러나 이미지를 increase 했을 경우, E픽셀은 항상 같기 때문에 다음과 같은 문제가 생긴다.

<img src="/seam_caving/image/dolphin/dolphin2.png" width="50%" height="50%" title="dolphin2" alt="dolphin2"></img><br/>

이런 문제를 해결하기 위해 논문에서 제시한 방법에 따라 다음과 같이 seam을 구성한다.

<img src="/seam_caving/image/dolphin/dolphin3.png" width="50%" height="50%" title="dolphin3" alt="dolphin3"></img><br/>

다음과 같이 결과가 출력된다.

<img src="/seam_caving/image/dolphin/dolphin5.png" width="50%" height="50%" title="dolphin5" alt="dolphin5"></img><br/>

----------------------------------------------------------------------

## 활용

Seam Caving 알고리즘을 이용해 몇가지 기능을 구현할 수 있다.
이미지를 일반적인 방법으로 크게 늘린 후, Seam Caving을 사용해 원래 크기로 줄인다면 다음과 같이 핵심 오브젝트만 커지는 결과를 만들 수 있다.

<p float="left">
<img src="/seam_caving/image/increase object/increase object1.png" width="30%" height="30%" title="increase object1" alt="increase object1"></img>  --->  
<img src="/seam_caving/image/increase object/increase object2.png" width="30%" height="30%" title="increase object2" alt="increase object2"></img><br/>
</p>


이미지에서 특정 오브젝트를 강제로 낮은 E값을 갖게 하여 해당 오브젝트를 삭제할 수도 있다.
<p float="left">
<img src="/seam_caving/image/remove object/remove object1.png" width="30%" height="30%" title="remove object1" alt="remove object1"></img>  --->  
<img src="/seam_caving/image/remove object/remove object2.png" width="30%" height="30%" title="remove object2" alt="remove object2"></img><br/>
</p>

----------------------------------------------------------------------

Reference   
[Shai Avidan, Ariel Shamir, "Seam Carving for Content-Aware Image Resizing", ACM Transactions on Graphics, Volume 26, Number 3, SIGGRAPH 2007](https://perso.crans.org/frenoy/matlab2012/seamcarving.pdf)
