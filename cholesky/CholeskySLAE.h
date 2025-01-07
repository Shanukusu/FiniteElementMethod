#pragma once

#include <vector>
#include <utility>

namespace Cholesky {

	/**
	 * @brief Класс для поиска частного решения СЛАУ методом Холецкого
	 *
	 * Класс решает квадратную Системы Линейных Алгебраических Уравнений методом Холецкого
	 *										A * x = b
	 * Выполняет A = LU разложение предоставляемой ленточной матрицы с половиной длины ленты L
	 * После которого находит x следующими вычислениями
	 *								  L^T * x = y, L * y = b
	 */
	class CholeskySLAE {
	public:
		/**
		 * @brief Конструктор для системы
		 *
		 * Метод выделяет память под квадратную ленточную матрицу и вектор правой части
		 * При создании A, b заполнены 0ми
		 *
		 * @pre Оба параметра должны быть не отрицательными
		 * @pre Половина длины ленты должна быть меньше количества строк
		 *
		 * @param L Половина длины ленты (вся длина 2L-1)
		 * @param rows Количество строк/столбцов в квадратной матрице
		 */
		CholeskySLAE(int L, int rows);

		/**
		 * @brief Выставляет значение в матрице СЛАУ
		 *
		 * @pre Элемент матрицы, к которому производится обращение, должен быть в пределах
		 *		ленты. Это можно проверить методом isMatrixAccessInBounds(int row, int column)
		 *
		 * @param row Строка в матрице
		 * @param column Столбец матрицы
		 * @param value Значение, которое выставляется
		 */
		void setElem(int row, int column, double value);

		/**
		 * @brief Выставляет значение в векторе правой части СЛАУ
		 *
		 * @pre Элемент не выходит за пределы вектора (0 <= elem < rows)
		 *
		 * @param elem Индекс элемента в векторе
		 * @param value Значение, которое выставляется
		 */
		void setRightSide(int elem, double value);

		/**
		 * @brief Проверяет, если для указанных параметров, элемент находится на ленте
		 *
		 * @param row Строка в матрице
		 * @param column Столбец матрицы
		 * @return Истина, если элемент попадает на ленту, и обращение к setElem по этому адресу не вызовет
		 *			исключения
		 *		   Ложь - иначе
		 */
		bool isMatrixAccessInBounds(int row, int column);


		/**
		 * @brief Находит частное решение СЛАУ A*x = b методом Холецкого
		 *
	     * @pre Матрица A должна быть не вырожденной
		 *
		 * @param verbose Выводит дебаг информацию в консоль, выводит целую матрицу, так что при больших rows будет страшно
		 *
		 * @return частное решение СЛАУ
		 */
		std::vector<double> solve(bool verbose = false);

		void print(); //TODO: удали меня
	private:
		// Ты ищешь тут документацию? зачем?
		// Если что-то сломано, то напиши мне в чате, я исправлю, так что кышь отседа
		int rows;
		int L;
		std::vector<std::vector<double>> strips;
		std::vector<double> rightSide;

		std::pair<int, int> convertIndecesToInner(int row, int column);
		std::pair<int, int> convertInnerToIndeces(int i, int j);

		double getElem(int row, int column, double default_value = 0.0, bool throwing = false);
		CholeskySLAE getLowerMatrix();
	};
};