const myArray = [];

for (let i = 0; i < 100; i++) {
  myArray[i] = Math.floor(Math.random() * 100);
}

function mySelectionSort(array) {
  const jopArray = [...array];
  let count = 0;
  for (let i = 0; i < jopArray.length; i++) {
    for (let j = 0; j < jopArray.length; j++) {
      count++;
      if (jopArray[j] > jopArray[i]) {
        [jopArray[i], jopArray[j]] = [jopArray[j], jopArray[i]];
      }
    }
  }
  console.log(`mySelectionSort: ${count}`);
  return jopArray;
}
