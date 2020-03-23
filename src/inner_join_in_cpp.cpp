#include <iostream>
#include <vector>
#include <map>

/* Постановка задачи:
 *
 * 1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и map[i];
 * 2.удалить случайное число элементов (не более 15) в каждом контейнере;
 * 3.после этого провести синхронизацию, чтобы в vector и map остались
 * только имеющиеся в обоих контейнерах элементы (дубликаты не удалять).
 *
 */

//Выводим текущие значения контейнеров
void printData(const std::vector<int>& vec, const std::map<int,int>& Map){
	std::cout<<"Vector:"<<std::endl;
	for(auto s: vec)
		std::cout<<s<<" ";
	std::cout<<"\n\nMap:\n";
	for(auto s: Map)
		std::cout<<s.first<<":"<<s.second<<std::endl;
	std::cout<<std::endl;
}

//Генерируем 20 чисел для каджого контейнера. Числа добавляем по модулю maxNum
void generate_data(std::vector<int>& vec, std::map<int,int>& Map, int maxNum){
	for(int i=0;i<20;i++){
			int temp =rand()%(maxNum+1);
			vec.push_back(temp);
			Map[temp]++;
		}
}

int main() {
	int maxNum=9;
	std::vector<int> vec;
	std::map<int,int> Map;

	generate_data(vec,Map,maxNum);
	std::cout<<"Generated data:"<<std::endl;
	printData(vec,Map);

	//удаляем случайное количество чисел из каждого контейнера (но не больше 15)
	for(int i=0;i<rand()%15;i++){
		vec.erase(vec.begin()+rand()%(vec.size()-i));

		/*В map удаление происходит по ключу, поэтому мы генерируем случайное
		 *  число меньше Map.size(), это будет порядковым номером элемента, который мы будем удалять.
		 *  Итерируемся по словарю, чтобы найти нужный элемент.

		 *  Словарь организован таким образом, что ключи- это сгенерированные числа,
		 *  а значения- это количество раз, сколько они встречаются, поэтому удаление
		 *  числа из словаря это просто уменьшение его количества на 1.
		 *  Если это количество становится равно 0, удаляем данный элемент, чтобы избежать ситуации,
		 *  когда rand() скажет нам еще раз его удалить (когда там 0), и не сделать значение отрицательным

		 *  Одновременное итерирование по словарю и удаление из него элементов
		 *  является плохой практикой, но в данном случае сразу после удаления,
		 *  итерирование прекращается, поэтому ошибок не возникнет*/

		int index_to_delete = rand()% Map.size();
		int j=0;
		for(auto& s: Map){
			if(j==index_to_delete){
				s.second--;
				if(s.second==0)
					Map.erase(s.first);
				break;
			}
			j++;
		}
	}

	std::cout<<"Containers after deleting random elements:"<<std::endl;
	printData(vec, Map);

	/*Будем итерироваться по вектору, и проверять наличие каждого
	 * его элемента в словаре. Если элемент есть, добавим его и его
	 * количество в доп словарь temp (который будет конечным ответом),
	 * если элемента нет в словаре, удалим его и из вектора.

	 * Итерирование здесь происходит по интексам, поэтому проблем из-за
	 * одновременного итерирования и удаления быть не должно*/

	std::map<int, int> temp;
	for(unsigned int i=0;i<vec.size();i++){
		if(Map[vec[i]]==0){
			vec.erase(vec.begin()+i);
			i--;
		}else
			temp[vec[i]]=Map[vec[i]];
	}

	std::cout<<"Synchronized containers:"<<std::endl;
	printData(vec,temp);

	return 0;
}
