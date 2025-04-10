import { cs50Projects } from '../data/projects-cs50.js';

function renderProjectCard() {
  const projectCards = cs50Projects;
  let projectHTML = ``;

  projectCards.forEach((project) => {
    projectHTML += `  
          <div class="project-card">
            <img src="${project.image}" alt="${project.name}" class="project-img" />
            <h3>${project.name}</h3>
            <p>${project.description}</p>
          </div>`;
  });
  document.querySelector('.js-project-card').innerHTML = projectHTML;
}
renderProjectCard();
