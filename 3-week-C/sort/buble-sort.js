const myArray = [];

for (let i = 0; i < 100; i++) {
  myArray[i] = Math.floor(Math.random() * 100);
}

function myBubleSort(array) {
  const secondArray = [...array];
  let count = 0;
  for (let i = 0; i < secondArray.length; i++) {
    let swapped = false;
    for (let j = 0; j < secondArray.length - 1 - i; j++) {
      count++;
      if (secondArray[j] > secondArray[j + 1]) {
        [secondArray[j], secondArray[j + 1]] = [
          secondArray[j + 1],
          secondArray[j],
        ];
        swapped = true;
      }
    }
    if (!swapped) break;
  }
  console.log(`myBubleSort: ${count}`);
  return secondArray;
}
