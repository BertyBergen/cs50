const myArray = [];

for (let i = 0; i < 100; i++) {
  myArray[i] = Math.floor(Math.random() * 100);
}

function mergeSort(array) {
  recursiveCalls++; // Count recursive calls
  if (array.length <= 1) {
    return array;
  }

  const mid = Math.floor(array.length / 2);
  const left = mergeSort(array.slice(0, mid));
  const right = mergeSort(array.slice(mid));

  return merge(left, right);
}

function merge(left, right) {
  let result = [];
  let i = 0,
    j = 0;

  while (i < left.length && j < right.length) {
    comparisons++; // Count comparisons
    if (left[i] < right[j]) {
      result.push(left[i]);
      i++;
    } else {
      result.push(right[j]);
      j++;
    }
  }

  merges += left.length - i + right.length - j; // Count merges
  return result.concat(left.slice(i)).concat(right.slice(j));
}

mergeSort(myArray);
