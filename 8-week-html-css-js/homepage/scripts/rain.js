let nbDrop = 358;

function randRange(minNum, maxNum) {
  return Math.floor(Math.random() * (maxNum - minNum + 1) + minNum);
}

function createRain() {
  let rainContainer = document.querySelector('.rain');
  for (let i = 0; i < nbDrop; i++) {
    let dropLeft = randRange(0, window.innerWidth);
    let dropTop = randRange(-1000, 0); // Start from above the screen

    let drop = document.createElement('div');
    drop.classList.add('drop');
    drop.style.left = `${dropLeft}px`;
    drop.style.top = `${dropTop}px`;
    drop.style.animationDuration = `${randRange(2, 5)}s`; // Random speed for each drop
    drop.style.animationDelay = `${randRange(0, 5)}s`; // Random delay for starting the animation

    rainContainer.appendChild(drop);
  }
}

createRain();
document.body.addEventListener('click', function () {
  window.location.href = '../animations.html';
});
