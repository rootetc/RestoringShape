# RestoringShape
## Object
-  납땜의 불량 여부를 검사하기 위해서는 숙달된 전문가가 필요하며 검사 시 상당한 시간 소요가 발생 한다. 
=====> 소요 시간 단축을 통하여 생산성 향상을 목표로 한다.     
- 상품에 대한 품질 검사를 위하여 2D 알고리즘을 활용하였으며 2D 알고리즘의 신뢰성을 높이기 위해  3D 형상 복원 프로그램 제작. 

## Principle
![default](https://cloud.githubusercontent.com/assets/19329620/16171618/3f7feb7a-35ae-11e6-88df-cb3972018fcc.png)
- 왼쪽 그림의 좌표는 raw data일 때 각 좌표들이 의미 하는 값이다.
오른쪽 그림은는 cylinderical coordinates system을 orthogonal coordinates system으로 변환 후 좌표의 모습이다.  
가로의 좌표의 계수가 N라고 가정을 한다면 각 점 theta의 값은 로 표현 할 수 있다. 
또한 각 점의 index number를 활용하여 해당 점의 모든 각도를 구할 수 있으며 각 점의 indext를 라고 나타내면 로 모든 점에 대한 각 정보를 얻을 수 있다.  
각 점의 세로에 값을 로 정의 한다. cylinderical coordinates에서 orthogonal coordinates의 x, y 좌표에 해당 하는 값을 구하기 위하여 Euler's identity을 사용 할 수 있다.
![default](https://cloud.githubusercontent.com/assets/19329620/16171632/c1d1c594-35ae-11e6-8b2a-cad8b3f3c4a2.png)으로 식을 변환 할 수 있다.

## Block diagram






