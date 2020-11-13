const timsort = require('bindings')('timsort');
const TimSort = require('timsort');

const length = 1000000;

const arr = Array.from({ length }, (_, i) => i);
const arr2 = Array.from({ length }, (_, i) => length - i);

const shuffle = array => {
  let tmp, current, top = array.length - 1;

  if (top) {
    while(top) {
      current = Math.floor(Math.random() * (top + 1));
  
      tmp = array[current];
      
      array[current] = array[top];
      array[top] = tmp;

      --top;
    }
  } 
  return array;
}

shuffle(arr)

// console.time('timsort');
// console.log(timsort.sort(arr2));
// console.timeEnd('timsort');

// console.time('timsortJs');
// console.log(TimSort.sort(arr2));
// console.timeEnd('timsortJs');

// console.time('jssort');
// console.log(arr2.sort((a, b) => a - b));
// console.timeEnd('jssort');

// const marr = new Float64Array([ 441, 438, 440, 439, 442 ]);
// const buff = Buffer.from(marr.buffer);
// console.log(buff);
// console.log(marr.buffer);
// console.log(timsort.sort(Buffer.from(marr.buffer)));


// console.time('timsortBuffer');
// const marr = new Float64Array(arr);
// console.log(timsort.sortBuffer(Buffer.from(marr.buffer)));
// console.timeEnd('timsortBuffer');

console.time('timsort');
console.log(timsort.sort(arr));
console.timeEnd('timsort');

console.time('timsortJs');
console.log(TimSort.sort(arr));
console.timeEnd('timsortJs');

// console.time('jssort');
// console.log(arr.sort((a, b) => a - b));
// console.timeEnd('jssort');