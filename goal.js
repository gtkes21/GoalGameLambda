const bombImg = "https://freesvg.org/img/bomb.png";
const ballImg = "https://turbo-next.spribegaming.com/ball.7400b4088128521bcd5f.svg";
const bombDetonation = "https://turbo-next.spribegaming.com/bomb_detonation.5ff2455899c2d3887067.svg";
const plus_minus = document.querySelectorAll(".bet-change");
const betDisplay = document.querySelector("input");
const fixed_bets = document.querySelectorAll(".default-bets");
const fields = document.querySelectorAll(".field");
const sizeButtons = document.querySelectorAll('.sizeBut');
const clickSound =  new Audio('mixkit-game-click-1114-[AudioTrimmer.com] (1).wav');
let currBet = 2.00;
let balance = 9999.00;
let maxRow = 4;
let maxCol = 7;
let currCol = 0;
let currFieldSize = document.querySelector("#activeSize");
let gameInAction = false;

let ball = document.createElement('img');
ball.src = ballImg;
ball.style.height = "50px";
ball.style.width = "50px";

function displayBet(){
    betDisplay.value = currBet.toFixed(2);
}

function changeBet(){
    betDisplay.addEventListener('blur', function (event) {
        if(!gameInAction){
            clickSound.play();
            currBet = +event.target.value;
            if(currBet > 100.00) currBet = 100.00;
            if(currBet < 0.00) currBet = 0.10;
            displayBet();
        }
    });
    plus_minus[0].addEventListener('click',function(){
        if(!gameInAction){
            clickSound.play();
            currBet -= 0.10;
            if(currBet <= 0) currBet = 0.1;
            displayBet();
        }
    });
    plus_minus[1].addEventListener('click',function(){
        if(!gameInAction){
            clickSound.play();
            currBet += 0.10;
            if(currBet>=100.00) currBet = 100.00;
            displayBet();    
        }
    });
    fixed_bets[0].addEventListener('click',function(evt){
        clickSound.play();
        currBet = +evt.target.innerText.substring(0,evt.target.innerText.length-1)
        displayBet();
    });
    fixed_bets[1].addEventListener('click',function(evt){
        clickSound.play();
        currBet = +evt.target.innerText.substring(0,evt.target.innerText.length-1)
        displayBet();
    });
    fixed_bets[2].addEventListener('click',function(evt){
        clickSound.play();
        currBet = +evt.target.innerText.substring(0,evt.target.innerText.length-1)
        displayBet();
    });
    fixed_bets[3].addEventListener('click',function(evt){
        clickSound.play();
        currBet = +evt.target.innerText.substring(0,evt.target.innerText.length-1)
        displayBet();
    });
}

function showField(show,hidden1,hidden2){
    show.classList.remove("hidden");
    hidden1.classList.add("hidden");
    hidden2.classList.add("hidden");
}

function changeActiveSize(value){
    currFieldSize.removeAttribute('id');
    currFieldSize = value;
    switch(currFieldSize.innerText){
        case 'Small':
            maxRow = 3;
            maxCol = 4;
            break;
        case 'Medium':
            maxRow = 4;
            maxCol = 7;
            break;
        case 'Big':
            maxRow = 5;
            maxCol = 10;
            break;
    }
    currCol = 0;
    currFieldSize.id = 'activeSize';
}

function setActiveCol(){
    let obj = document.querySelectorAll(`.field-box-${currFieldSize.innerText.toLowerCase()}`);
    let oddBoxes = document.querySelectorAll(`.odd-box-${currFieldSize.innerText.toLowerCase()}`);
    for (let i = 0; i < maxRow; i++) {
        obj[maxRow * currCol + i].id="activeCol";
        oddBoxes[currCol].id = "activeOdd"
    }
}

function changeFieldSize(){
    sizeButtons[0].addEventListener('click',function(){
        clickSound.play();
        changeActiveSize(sizeButtons[0]);
        showField(fields[0],fields[1],fields[2]);
        setActiveCol();
    });
    sizeButtons[1].addEventListener('click',function(){
        clickSound.play();
        changeActiveSize(sizeButtons[1]);
        showField(fields[1],fields[0],fields[2]);
        setActiveCol();
    });
    sizeButtons[2].addEventListener('click',function(){
        clickSound.play();
        changeActiveSize(sizeButtons[2]);
        showField(fields[2],fields[0],fields[1]);
        setActiveCol();
    });
}

function blockParam(){
    for(const a of document.querySelectorAll(".param-box>*")){
        a.style.opacity = 0.8;
        a.classList.add("not-clickable");
    }
    
}

function generateBombs(){
    const boxArr = document.querySelectorAll(`.field-box-${currFieldSize.innerText.toLowerCase()}`);
    for (let i = 0; i < maxCol; i++){
        let idx = i*(maxRow) + Math.floor(Math.random()*(maxRow-1));
        let img = document.createElement('img');
        img.src = bombImg;
        img.style.height = "50px";
        img.style.width = "50px";
        img.classList.add("hidden"); 
        boxArr[idx].appendChild(img);
        img.parentElement.classList.add("bomb");
    }
}

async function play(){
    const boxArr = document.querySelectorAll("#activeCol");
    for (let i = 0; i < maxRow; i++) {
        const element = boxArr[i];
        element.addEventListener('click',function(event){
            console.log("gol");
            console.log(event.target.classList.contains("bomb"));
            event.target.appendChild(ball);
            for (let j = 0; j < boxArr.length; j++) {
                const elemen2 = boxArr[j];
                elemen2.removeAttribute('id');
            }
            currCol++;
            setActiveCol();
        });
    }
}

async function betButton(){
    document.querySelector('.bet-button').addEventListener('click',async function(){
        clickSound.play();
        blockParam();
        setActiveCol();
        generateBombs();
        play().then(console.log("va"));
    });
}

function init(){
    changeBet();
    changeFieldSize();
    betButton();
    
    
}  
    

init();
