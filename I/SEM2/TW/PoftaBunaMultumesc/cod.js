// modificarea stilului unui element sau al unui grup de elemente
// manipularea DOM-ului (selectare dupa id, tag, clasa, folosind selectori CSS)
// crearea si stergerea de elemente HTML
// folosirea și modificarea evenimentelor generate de mouse si tastatură
// schimbarea aleatoare a valorilor unor proprietati (de exemplu: culoare, dimensiuni, pozitie)

function imgSlider(anything){
    document.querySelector('.burger').src = anything;
}

function changeCircleColor(color){
    const circle = document.querySelector('.circle');
    circle.style.background = color;
}

// toggle menu pentru versiunile mobile / tableta
function toggleMenu() {
    const toggle = document.querySelector('.toggle');
    const nav = document.querySelector('.navigation');
    const iconMenu = toggle.querySelector('.icon-menu');
    const iconClose = toggle.querySelector('.icon-close');

    nav.classList.toggle('active');
    toggle.classList.toggle('active');

    if (nav.classList.contains('active')) {
        iconMenu.style.display = 'none';
        iconClose.style.display = 'block';
    } else {
        iconMenu.style.display = 'block';
        iconClose.style.display = 'none';
    }
}

// abonare la newsletter
function toggleNewsletter() {
    const email = prompt("Introduceți adresa de email pentru a vă abona la newsletter:");
    
    if (email) {
        // validare simpla de email
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        
        if (emailRegex.test(email)) {
            alert("Mulțumim! V-ați abonat cu succes la newsletter-ul nostru!");
            console.log("Email abonat:", email);
        } else {
            alert("Vă rugăm să introduceți o adresă de email validă.");
        }
    }
}


//ca sa mearga fie validare cont/ searchbar, trebuie comentat codul pentru unul din ele

//searchbar pentru retete
const searchBtn = document.getElementById('search-btn');
const mealList = document.getElementById('meal');
const mealDetailsContent = document.querySelector('.meal-details-content');
const recipeCloseBtn = document.getElementById('recipe-close-btn');


searchBtn.addEventListener('click', getMealList);
mealList.addEventListener('click', getMealRecipe);
recipeCloseBtn.addEventListener('click', () => {
    mealDetailsContent.parentElement.classList.remove('showRecipe');
});


// lista de retete care se pot face cu ingredientele date
function getMealList(){
    let searchInputTxt = document.getElementById('search-input').value.trim();
    fetch(`https://www.themealdb.com/api/json/v1/1/filter.php?i=${searchInputTxt}`)
    .then(response => response.json())
    .then(data => {
        let html = "";
        if(data.meals){
            data.meals.forEach(meal => {
                html += `
                    <div class = "meal-item" data-id = "${meal.idMeal}">
                        <div class = "meal-img">
                            <img src = "${meal.strMealThumb}" alt = "food">
                        </div>
                        <div class = "meal-name">
                            <h3>${meal.strMeal}</h3>
                            <a href = "#" class = "recipe-btn">Get Recipe</a>
                        </div>
                    </div>
                `;
            });
            mealList.classList.remove('notFound');
        } else{
            html = "Nu am găsit nicio rețetă :(";
            mealList.classList.add('notFound');
        }

        mealList.innerHTML = html;
    });
}


// getter pentru reteta
function getMealRecipe(e){
    e.preventDefault();
    if(e.target.classList.contains('recipe-btn')){
        let mealItem = e.target.parentElement.parentElement;
        fetch(`https://www.themealdb.com/api/json/v1/1/lookup.php?i=${mealItem.dataset.id}`)
        .then(response => response.json())
        .then(data => mealRecipeModal(data.meals));
    }
}


// modal pentru afisarea retetei 
function mealRecipeModal(meal){
    console.log(meal);
    meal = meal[0];
    let html = `
        <h2 class = "recipe-title">${meal.strMeal}</h2>
        <p class = "recipe-category">${meal.strCategory}</p>
        <div class = "recipe-instruct">
            <h3>Instructions:</h3>
            <p>${meal.strInstructions}</p>
        </div>
        <div class = "recipe-meal-img">
            <img src = "${meal.strMealThumb}" alt = "">
        </div>
        <div class = "recipe-link">
            <a href = "${meal.strYoutube}" target = "_blank">Watch Video</a>
        </div>
    `;
    mealDetailsContent.innerHTML = html;
    mealDetailsContent.parentElement.classList.add('showRecipe');
}