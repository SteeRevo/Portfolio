

let filler;
let gunSound;
let song;



function preload() {
  customFont = loadFont('strenuous cast.otf');
  customFont2 = loadFont('Octynaz Regular.ttf');
  soundFormats('mp3', 'ogg');
  gunSound = loadSound('gunshot.mp3');
  song = loadSound('godot.mp3');
  song.setVolume(0.5);
  
  
}


function setup() {
  song.play();
  createCanvas(800,1000);
  textSize(200);
  textAlign(LEFT, CENTER);
  y_val = random(50, 750);
  xStart = -300;
  xStart2 = 900;
  xStart3 = -500;
  xStart4 = 1000;
  yStart = 25;
  yStart2 = 250;
  yStart3 = 500;
  yStart4 = 725;
  
  xStart5 = -300;
  xStart6 = 900;
  xStart7 = -300;
  yStart5 = 70;
  yStart6 = 300;
  yStart7 = 700;
   
  title1 = 'PHOENIX';
  title2 = 'WRIGHT';
  title3 = 'ACE';
  title4 = 'ATTORNEY';

  title1_x = 300;
  title1_y = 100;

  title2_x = -20;
  title2_y = 350;

  title3_x = 580;
  title3_y = 600;

  title4_x = 0;
  title4_y = 850;

  draw_words = false;
  highlight = false;
  miles_poster = false;
  choice_screen = true;
  fail_screen = false


  s = 'Evidence';
  s2 = 'Contradictions';
  s3 = 'Truth';
  s4 = 'Justice';
  s5 = "Maya Fey";
  s6 = "Pearl Fey";
  s7 = "Miles Edgeworth";
  
  
  shot1 = false;
  shot2 = false;
  shot3 = false;
  shot4 = false;
  shot5 = false;
  shot6 = false;
  shot7  = false;
  shot_next = false;
  shotall = false;
  retry_screen = false;
  timer = 25;
  pause = 5;
  
  
  
  Phoenix_words = ["Miles Edgeworth", "Franziska von Karma", "Manfred von Karma", "Lies", "Deceit", "Corruption", "Falsified Evidence", "Godot", "Witness Testimony", "Shelley de Killer", "Murder", "Dahlia Hawthorne"];
  
  class hold_words{
    constructor(words){
      this.word_array = words;
      this.filler_x = [-random(950,1200), random(950,1200),-random(950,1200), random(950,1200), -random(950,1200), random(950,1200), -random(950,1200), random(950,1200), -random(950,1200), random(950,1200), -random(950,1200), random(950,1200)];
      this.filler_y = [random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750), random(0, 750)];
    }
    
    display(i, d, fSize, speed){
      textSize(fSize);
      textFont(customFont);
      fill('#0D0A10')
      text(this.word_array[i], this.filler_x[i], this.filler_y[i]);
      if(d == 0){
        this.filler_x[i] += speed;
        if(this.filler_x[i] > 800){
          this.filler_x[i] = -900;
        }
      }
      
      if(d == 1){
        this.filler_x[i] -= speed;
        if(this.filler_x[i] < -900){
          this.filler_x[i] = 900;
        }
      }
      
     
    }
  }
  
  filler = new hold_words(Phoenix_words);
  input = createInput();
  input.position(325, 700);
  
  
}

function keyPressed(){
  if(choice_screen == true && keyCode == ENTER){
    if(input.value() == 'Yes' || input.value() == 'yes'){
      choice_screen = false;
      input.remove();
    }
    if(input.value() == 'No' || input.value() == 'no'){
      fail_screen = true;
      choice_screen = false;
    }
  }
    
}

  

function draw() {
  
  if(choice_screen == true && fail_screen == false){
    
    background('#0D0A10');
    textSize(75);
    textFont(customFont2);
    fill('#F0E8DB');
    text('Will you search for justice', 100, 300);
    text('in spite of the hardships?', 150, 500);
  }
  else if(fail_screen == true && choice_screen == false){
    background('#0D0A10');
    textSize(100);
    textFont(customFont);
    fill('#F0E8DB');
    text('guilty', 250, 300);
    textSize(40)
    text('reload to try again', 200, 400)
    input.remove();
  }
  
  if(draw_words == false  && choice_screen == false && fail_screen == false && shotall == false){
    background('#257BA0');
    click_text();
    
  }
  else if(draw_words == true){
    
    check_phoenix_poster();
   
    
  }
  else if(shotall == true){
    background('#0D0A10');
    textFont(customFont2);
    textSize(50);
    fill('#F0E8DB');
    text('You had faith and prevailed', 110, 900);
    text('Not guilty verdict with ' + timer + ' seconds left', 130, 950);
    
    
  }
 
  
}


function mouseClicked() {
  if ((isMouseInsideTextOct(title1, title1_x, title1_y) ||
      isMouseInsideTextOct(title2, title2_x, title2_y) ||
      isMouseInsideTextOct(title3, title3_x, title3_y) ||
      isMouseInsideTextOct(title4, title4_x, title4_y)) && (choice_screen == false && fail_screen == false)) {
    draw_words = true;
  }
  if(isMouseInsideText(s, xStart, yStart) && shot1 == false){
    gunSound.play();
    shot1 = true;
  }
  if(isMouseInsideText(s2, xStart2, yStart2) && shot2 == false){
    gunSound.play();
    shot2 = true;
  }
  if(isMouseInsideText(s3, xStart3, yStart3) && shot3 == false){
    gunSound.play();
    shot3 = true;
  }
  if(isMouseInsideText(s4, xStart4, yStart4) && shot4 == false){
    gunSound.play();
    shot4 = true;
  }
  if(isMouseInsideText(s5, xStart5, yStart5) && shot5 == false){
    gunSound.play();
    shot5 = true;
  }
  if(isMouseInsideText(s6, xStart6, yStart6) && shot6 == false){
    gunSound.play();
    shot6 = true;
  }
  if(isMouseInsideText(s7, xStart7, yStart7) && shot7 == false && (shot1 && shot2 && shot3 && shot4)){
    gunSound.play();
    shot7 = true;
  }
  
  
}

function isMouseInsideTextOct(message, messageX, messageY) {
  const messageWidth = textWidth(message);
  const messageTop = messageY - textAscent() + 120;
  const messageBottom = messageY + textDescent() + 50;
  if(mouseX > 800){
    return false;
  }

  return mouseX > messageX && mouseX < messageX + messageWidth &&
    mouseY > messageTop && mouseY < messageBottom;
}

function isMouseInsideText(message, messageX, messageY) {
  const messageWidth = textWidth(message) + 200;
  const messageTop = messageY - textAscent();
  const messageBottom = messageY + textDescent();
  if(mouseX > 800){
    return false;
  }

  return mouseX > messageX && mouseX < messageX + messageWidth &&
    mouseY > messageTop && mouseY < messageBottom;
}

function click_text(){
  if (isMouseInsideTextOct(title1, title1_x, title1_y) || 
      isMouseInsideTextOct(title2, title2_x, title2_y) ||
      isMouseInsideTextOct(title3, title3_x, title3_y) ||
      isMouseInsideTextOct(title4, title4_x, title4_y)
     ){
    fill('#EE5622');
  }
  else{
    fill('#F0E8DB');
  }
  background('#257BA0');
  textFont(customFont2);
  textSize(200);
  text(title1, 300, 100);
  text(title2, -10, 350);
  text(title3, 580, 600);
  text(title4, -10, 850);
}

function check_phoenix_poster(){
  background('#257BA0');
  if(timer == 0){
    fail_screen = true;
    draw_words = false;
  }
  if(frameCount % 60 == 0 && timer > 0 && shotall == false){
    timer --;
  }
  textSize(20);
  if(isMouseInsideText(s, xStart, yStart)){
    fill('#E26D5C');
  }
  else{
    fill('#0D0A10');
  }
  if(shot1){
    fill('#E26D5C')
  }
  
  if(shot1 == false && timer <= 20){
    textFont(customFont);
    text(s, xStart, yStart);
    xStart += 5;
  }
  if(xStart > 800){
    xStart = -300;
  }

  if(isMouseInsideText(s2, xStart2, yStart2)){
    fill('#E26D5C');
  }
  else{
    fill('#0D0A10');
  }
  if(shot2){
    fill('#E26D5C')
  }
  if(shot2 == false && timer <= 20){
    textFont(customFont);
    text(s2, xStart2, yStart2);
    xStart2 -= 7;
  }
  if(xStart2 < -150){
    xStart2 = 900;
  }

  if(isMouseInsideText(s3, xStart3, yStart3)){
    fill('#E26D5C');
  }
  else{
    fill('#0D0A10');
  }
  if(shot3){
    fill('#E26D5C');
  }
  
  if(shot3 == false && timer <= 20){
    textFont(customFont);
    text(s3, xStart3, yStart3);
    xStart3 += 10;
  }
  
  if(xStart3 > 800){
    xStart3 = -300;
  }
  
  if(isMouseInsideText(s4, xStart4, yStart4)){
    fill('#E26D5C');
  }
  else{
    fill('#0D0A10');
  }
  if(shot4){
    fill('#EE5622');
  }
  
  if(shot4 == false && timer <= 20){
    textFont(customFont);
    text(s4, xStart4, yStart4);
    xStart4 -= 6;
  }
  if(xStart4 < -150){
    xStart4 = 1000;
  }
  if(shot1 && shot2 && shot3 && shot4){
    if(isMouseInsideText(s5, xStart5, yStart5)){
      fill('#EE5622');
    }
    else{
      fill('#0D0A10');
    }
    if(shot5){
      fill('#EE5622');
    }

    if(shot5 == false){
      textFont(customFont);
      text(s5, xStart5, yStart5);
      xStart5 += 10;
    }

    if(xStart5 > 800){
      xStart5 = -300;
    }

    if(isMouseInsideText(s6, xStart6, yStart6)){
      fill('#EE5622');
    }
    else{
      fill('#0D0A10');
    }
    if(shot6){
      fill('#EE5622');
    }

    if(shot6 == false){
      textFont(customFont);
      text(s6, xStart6, yStart6);
      xStart6 -= 6;
    }
    if(xStart6 < -150){
      xStart6 = 1000;
    }
    if(isMouseInsideText(s7, xStart7, yStart7)){
      fill('#EE5622');
    }
    else{
      fill('#0D0A10');
    }
    if(shot7){
      fill('#EE5622');
    }

    if(shot7 == false){
      textFont(customFont);
      text(s7, xStart7, yStart7);
      xStart7 += 10;
    }

    if(xStart7 > 800){
      xStart7 = -300;
    }
    
    
  }
  
  
  
  
  filler.display(0, 0, 20, 1);
  filler.display(1, 1, 40, 2);
  filler.display(2, 0, 50, 4);
  filler.display(3, 1, 80, 1);
  filler.display(4, 0, 40, 3);
  filler.display(5, 1, 60, 5);
  filler.display(6, 1, 80, 2);
  filler.display(7, 0, 40, 6);
  filler.display(8, 1, 60, 3);
  filler.display(9, 0, 20, 1);
  filler.display(10, 1, 40, 2);
  filler.display(11, 0, 80, 7);


  textFont(customFont2);
  fill('#F0E8DB');
  textSize(200);
  text(title1, 300, 100);
  text(title2, -10, 350);
  text(title3, 580, 600);
  text(title4, -10, 850);
  
  if(shot1){
    textSize(30)
    fill('#E26D5C');
    textFont(customFont);
    text(s, xStart, yStart);
  }
  if(shot2){
    textSize(30)
    fill('#E26D5C');
    textFont(customFont);
    text(s2, xStart2, yStart2); 
  }
  if(shot3){
    textSize(30)
    fill('#E26D5C');
    textFont(customFont);
    text(s3, xStart3, yStart3);
  }
  if(shot4){
    textSize(30)
    fill('#E26D5C');
    textFont(customFont);
    text(s4, xStart4, yStart4);
  }
  if(shot5){
    textSize(30)
    fill('#E26D5C');
    textFont(customFont);
    text(s5, xStart5, yStart5);
  }
  if(shot6){
    textSize(30);
    fill('#E26D5C');
    textFont(customFont);
    text(s6, xStart6, yStart6);
  }
  if(shot7){
    textSize(30);
    fill('#E26D5C');
    textFont(customFont);
    text(s7, xStart7, yStart7);
  }
  
  textSize(40);
  fill('#F0E8DB');
  textFont(customFont2);
  text(timer, 700, 25);
  
  if(shot6 && shot5 && shot7){
    shotall = true;
    if(frameCount % 60 == 0 && pause > 0){
      pause --;
    }
    if(pause == 0){
      draw_words = false;
    }
    
  }
  
  
}

