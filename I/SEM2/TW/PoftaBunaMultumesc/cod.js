// modificarea stilului unui element sau al unui grup de elemente
// manipularea DOM-ului (selectare după id, tag, clasă, folosind selectori CSS)
// crearea și stergerea de elemente HTML
// folosirea și modificarea evenimentelor generate de mouse si tastatură
// schimbarea aleatoare a valorilor unor proprietăți (de exemplu: culoare, dimensiuni, poziție)

function imgSlider(anything){
    document.querySelector('.burger').src = anything;
}

function changeCircleColor(color){
    const circle = document.querySelector('.circle');
    circle.style.background = color;
}

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


// adaugare inputuri funcționale (de exemplu: input de tip text/range/number/radio/checkbox, select, textarea)

// // //CREARE CONT
// const regsiterForm = document.querySelector('.register-form');
// const submitBtn = document.getElementById('submit-btn');
// const submissionStatus = document.querySelector('.submission-status');

// // valori pentru input
// const firstName = document.getElementById('firstname'),
//       lastName = document.getElementById('lastname'),
//       emailAddr = document.getElementById('email'),
//       phoneNumber = document.getElementById('phonenumber'),
//       password = document.getElementById('password'),
//       confirmPassword = document.getElementById('confirm-password');


// submitBtn.addEventListener('click', (e) => {
//     e.preventDefault();
//     let isValidForm = validateInputValues();
//     if(isValidForm){
//         submissionStatus.classList.add('successMessage');
//         submissionStatus.textContent = "Registration succeeded!";
//     } else {
//         submissionStatus.classList.add('errorMessage');
//         submissionStatus.textContent = "Registration failed!";
//     }

//     setTimeout(() => {
//         submissionStatus.classList.remove('errorMessage', 'successMessage');
//     }, 1500);
// });

// function validateInputValues(){
//     let inputValidationStatus = [];  
//     if(validateName(firstName.value)){
//         inputStatus(true, firstName);
//         inputValidationStatus[0] = true;
//     } else {
//         inputStatus(false, firstName);
//         inputValidationStatus[0] = false;
//     }

//     if(validateName(lastName.value)){
//         inputStatus(true, lastName);
//         inputValidationStatus[1] = true;
//     } else {
//         inputStatus(false, lastName);
//         inputValidationStatus[1] = false;
//     }

//     if(validateEmail(emailAddr.value)){
//         inputStatus(true, emailAddr);
//         inputValidationStatus[2] = true;
//     } else {
//         inputStatus(false, emailAddr);
//         inputValidationStatus[2] = false;
//     }

//     if(validatePhoneNo(phoneNumber.value)){
//         inputStatus(true, phoneNumber);
//         inputValidationStatus[3] = true;
//     } else {
//         inputStatus(false, phoneNumber);
//         inputValidationStatus[3] = false;
//     }

//     if(validatePassword(password.value)){
//         inputStatus(true, password);
//         inputValidationStatus[4] = true;
//     } else {
//         inputStatus(false, password);
//         inputValidationStatus[4] = false;
//     }

//     if(confirmPassword.value.trim() !== "" && validateConfirmPassword(password.value, confirmPassword.value)){
//         inputStatus(true, confirmPassword);
//         inputValidationStatus[5] = true;
//     } else {
//         inputStatus(false, confirmPassword);
//         inputValidationStatus[5] = false;
//     }

//     return (inputValidationStatus.includes(false) ? false : true);
// } 

// // nume, prenume
// function validateName(nameTxt){
//     const nameRegex = /^[A-Za-z]+$/; // firstname or lastname containing only letters
//     return nameRegex.test(nameTxt);
// }

// // validare mail
// function validateEmail(emailTxt){
//     const emailRegex = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
//     return emailRegex.test(emailTxt);
// }

// //numar telefon
// function validatePhoneNo(phoneTxt){
//     const phoneRegex = /^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$/im;
//     /* formate acceptate
//         (123) 456-7890
//         (123)456-7890
//         123-456-7890
//         123.456.7890
//         1234567890
//         +31636363634
//         075-63546725
//     */
//    return phoneRegex.test(phoneTxt);
// }

// // validare parola
// function validatePassword(passwordTxt){
//     const passwordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/;
//     //minimum 8 caractere, cel putin o litera mare, una mica, o cifra si un caracter special
//     return passwordRegex.test(passwordTxt);
// }

// //confirmare parola
// function validateConfirmPassword(passwordTxt, confirmPasswordTxt){
//     return (passwordTxt == confirmPasswordTxt);
// }


// //eroare sau confirmare 
// function inputStatus(status, input){
//     let inputGroup = input.parentElement;
//     if(status){
//         inputGroup.classList.add('success');
//     } else {
//         inputGroup.classList.add('error');
//     }

//     //folosirea setTimeout sau setInterval
//     setTimeout(() => {
//         inputGroup.classList.remove('success', 'error');
//     }, 1500);
// }


//ca sa mearga fie validare cont/ searchbar, trebuie comentat codul pentru unul din ele

//searchbar pentru retete


const searchBtn = document.getElementById('search-btn');
const mealList = document.getElementById('meal');
const mealDetailsContent = document.querySelector('.meal-details-content');
const recipeCloseBtn = document.getElementById('recipe-close-btn');

// event listeners
searchBtn.addEventListener('click', getMealList);
mealList.addEventListener('click', getMealRecipe);
recipeCloseBtn.addEventListener('click', () => {
    mealDetailsContent.parentElement.classList.remove('showRecipe');
});


// get meal list that matches with the ingredients
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
            html = "Sorry, we didn't find any meal!";
            mealList.classList.add('notFound');
        }

        mealList.innerHTML = html;
    });
}


// get recipe of the meal
function getMealRecipe(e){
    e.preventDefault();
    if(e.target.classList.contains('recipe-btn')){
        let mealItem = e.target.parentElement.parentElement;
        fetch(`https://www.themealdb.com/api/json/v1/1/lookup.php?i=${mealItem.dataset.id}`)
        .then(response => response.json())
        .then(data => mealRecipeModal(data.meals));
    }
}


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