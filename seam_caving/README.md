SeamCaving

<p float="left">
<img src="/seam_caving/image/use image/input.jpg" width="30%" height="30%" title="input image" alt="input image"></img>  --->  
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
<img src="/seam_caving/image/use image/input.jpg" width="30%" height="30%" title="input image" alt="input image"></img>  --->  
<img src="/seam_caving/image/use image/seamcarving decrease.JPG" width="35%" height="35%" title="가로변환" alt="가로변환"></img>
<img src="/seam_caving/image/use image/seamcarving increase.JPG" width="30%" height="30%" title="세로변환" alt="세로변환"></img><br/>
</p>

...작성중

Reference   
[Shai Avidan, Ariel Shamir, "Seam Carving for Content-Aware Image Resizing", ACM Transactions on Graphics, Volume 26, Number 3, SIGGRAPH 2007](https://perso.crans.org/frenoy/matlab2012/seamcarving.pdf)
