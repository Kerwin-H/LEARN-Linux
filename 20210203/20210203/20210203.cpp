//����Linux�������ù��ߵ������ʵ��
//��ǿ���
//���쿪ʼ��git��linux



//������
int main(){
	int a[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
	int b[3][2];
	int i, j;
	printf("please enter a:\n");
	for (i = 0; i <= 1; i++){
		for (j = 0; j <= 2; j++){
			printf("%5d", a[i][j]);
			b[j][i] = a[i][j];         
		}
		printf("\n");
	}
	printf("this b is :\n");       
	for (i = 0; i <= 2; i++){
		for (j = 0; j <= 1; j++){
			printf("%5d", b[i][j]);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}
//====��дһ���򵥾���,Ѱ�������,����������к�
int main(){
	int i, j;
	int col = 0;
	int row = 0;
	int max;
	int a[3][4] = { { 1, 2, 3, 4 }, { 5, 8, 66, 21 }, { 4, 55, 71, 22 } };
	max = a[0][0];
	for (i = 0; i <= 2; i++){
		for (j = 0; j <= 3; j++){
			if (a[i][j] > max){
				max = a[i][j];
				row = i;
				col = j;
			}

		}
	}
	printf("this number is %d\nrow=%d  col=%d\n", max, i, j); 
	system("pause");
	return 0;
}
//====���������ӡһ������
int main(){
	char diamond[][5] = { { ' ', ' ', '*' }, { ' ', '*', ' ', '*' },
	{ '*', ' ', ' ', ' ', '*' }, { ' ', '*', ' ', '*' }, { ' ', ' ', '*' } };
	int i, j;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++)
			printf("%c", diamond[i][j]);
		printf("\n");
	}
	system("pause");
	return 0;
}