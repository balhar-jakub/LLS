void solveGem(floattype **matrix, floattype *result, size_t rowAmount)
{
    // Jako první dostanu zadanou matici, která je na pravé straně rozšířená o 
    // matici výsledků.
    // Jinak se jedná o matici čtvercovou, je to součástí zadání Gramovy matice.
    int actualRow = 0, innerRow;
    int actualColumn = 0, innerColumn;
    floattype valueOfActualRow, valueOfActualInnerRow;
    // Poslední řádek už je vyřešený
    //rowAmount je u čtvercové matice i, colsAmount pak i +1
    for(actualRow = 0; actualRow < rowAmount - 1; actualRow++, actualColumn++) {
        valueOfActualRow = matrix[actualRow][actualColumn];
        for(innerColumn = actualColumn; innerColumn < rowAmount + 1; innerColumn++) {
            matrix[actualRow][innerColumn] = matrix[actualRow][innerColumn] / valueOfActualRow;
            // V n-tém sloupci mám jedna, ve zbylých sloupcích mám původní 
            // hodnotu lomeno n tým sloupcem.
        }
        // Vezmu jeden po druhém řádky. 
        // První řádek vydělím prvním indexem a následně přičtu resp. 
        // odečtu od dalších řádků tolikrát, aby na zbylých řádcích byla v 
        // daném sloupci nula.
        // Začínám na dalším řádku než aktuálně jsem.
        for(innerRow = actualRow + 1; innerRow < rowAmount; innerRow++) {
            valueOfActualInnerRow = matrix[innerRow][actualColumn]; // Kolikrát je potřeba sluopec přičíst / odečíst
            // Provedu ve skutečnosti odečtení pro všechny sloupce.
            for(innerColumn = actualColumn; innerColumn < rowAmount + 1; innerColumn++) {
                matrix[innerRow][innerColumn] = matrix[innerRow][innerColumn] -
                        (valueOfActualInnerRow * matrix[actualRow][innerColumn]);
            }
        }
    }

    // V tenhle okamžik by měl být vypsán výsledek gemové matice, která je zadaná v parametru.
    printf("The result is:\n");
    for(actualRow = 0; actualRow < rowAmount; actualRow++){
        result[actualRow] = matrix[actualRow][rowAmount];
        printf("result na pozici %d=%f\n", actualRow + 1, matrix[actualRow][rowAmount]);
    }
}

void sortForPartialPivoting(floattype **matrix, size_t rowCount){
    // Pro všechny sloupce projdi všechny řádky a setřiď je tak, aby
    // v daném řádku byl nejvyšší hodnota z nepoužitých hodnot.
}
