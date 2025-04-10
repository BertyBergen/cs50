import { allQuestions } from './answers.js';

function shuffledArray(array) {
  const shuffled = [...array];
  for (let i = shuffled.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [shuffled[i], shuffled[j]] = [shuffled[j], shuffled[i]];
  }
  return shuffled;
}

const shuffledQuestions = shuffledArray(allQuestions);
const nextButton = document.querySelector('.button-next');

function displayQuestion(button) {
  let i = 0;
  const questionElement = document.querySelector('.questions');
  const answersElements = document.querySelector('.answers-block');

  function renderQuestion(index) {
    if (index >= shuffledQuestions.length) return;

    const currentQuestion = shuffledQuestions[index];
    const answers = shuffledArray([...currentQuestion.options]);

    questionElement.innerText = currentQuestion.question;
    answersElements.innerHTML = answers
      .map((answer) => `<button class="js-btn-answer">${answer}</button>`)
      .join('');

    const chooseButtons = document.querySelectorAll('.js-btn-answer');

    chooseButtons.forEach((btn) => {
      btn.addEventListener('click', function handleAnswerClick() {
        if (btn.innerText === currentQuestion.correct) {
          btn.classList.add('correct');
        } else {
          btn.classList.add('incorrect');
        }
        chooseButtons.forEach((btn) => btn.setAttribute('disabled', true));
      });
    });
  }

  renderQuestion(i);

  button.addEventListener('click', () => {
    if (i < shuffledQuestions.length - 1) {
      i++;
      renderQuestion(i);
    }
  });
}

displayQuestion(nextButton);

document.querySelector('.js-button-check').addEventListener('click', () => {
  const checkAnswer = document.querySelector('.js-input');
  const answer = 'switzerland';
  if (checkAnswer.value.toLowerCase() === answer) {
    checkAnswer.style.backgroundColor = 'green';
  } else {
    checkAnswer.style.backgroundColor = 'red';
  }
});
