canvas = document.getElementById("canvas");//ищем и сохраняем элемент canvas
ctx = canvas.getContext("2d"); //получаем контекст рисования
let value_R = 0;

// const centerX = canvas.width / 2;
// const centerY = canvas.height / 2;
// draw();

//Устанавливает новое значение R и вызывает функцию draw для перерисовки
function set_R_value(id){
    value_R = document.getElementById(id).value;
    document.getElementById('label_r').innerText = "R= " + value_R;
    if (value_R !== 0){
        draw();
    }else{
        alert("Введите какое-либо значение R");
    }
}



// function drawPoint(x,y,r) {
//     if(x > r+5 || y > r+5 || x < -1 * r-5 || y < -1 *r-5 ){
//         alert('Выход за пределы видимости графика\nНе могу отобразить точку');
//         draw();
//     }else {
//         draw();
//         ctx.fillStyle = "red";
//         ctx.beginPath();
//         ctx.moveTo(150, 70);
//         ctx.arc(150 + 50 * x / r, 70 - 50 * y / r, 3, 0, 2 * Math.PI);
//         ctx.closePath();
//         ctx.fill();
//     }
// }

function draw() {
    if (value_R == 1) {
        document.getElementById("b1").classList.add('active')
        document.getElementById('b2').classList.remove('active')
        document.getElementById('b3').classList.remove('active')
        document.getElementById('b4').classList.remove('active')
        document.getElementById('b5').classList.remove('active')
    }
    else if (value_R == 2) {
        document.getElementById("b2").classList.add('active')
        document.getElementById('b1').classList.remove('active')
        document.getElementById('b3').classList.remove('active')
        document.getElementById('b4').classList.remove('active')
        document.getElementById('b5').classList.remove('active')
    }
    else if (value_R == 3) {
        document.getElementById("b3").classList.add('active')
        document.getElementById('b1').classList.remove('active')
        document.getElementById('b2').classList.remove('active')
        document.getElementById('b4').classList.remove('active')
        document.getElementById('b5').classList.remove('active')
    }
    else if (value_R == 4) {
        document.getElementById("b4").classList.add('active')
        document.getElementById('b1').classList.remove('active')
        document.getElementById('b2').classList.remove('active')
        document.getElementById('b3').classList.remove('active')
        document.getElementById('b5').classList.remove('active')
    }
    else if (value_R == 5) {
        document.getElementById("b5").classList.add('active')
        document.getElementById('b1').classList.remove('active')
        document.getElementById('b2').classList.remove('active')
        document.getElementById('b3').classList.remove('active')
        document.getElementById('b4').classList.remove('active')
    }

}
//
//
//     ctx.clearRect(0, 0, 1000, 1000);
//
//     ctx.fillStyle = "rgba(91,95,201,0.58)";
//     ctx.beginPath();
//     ctx.moveTo(150, 70);
//
//     //сектор круга
//     ctx.arc(150, 70, 25, -4.7, 4 * Math.PI / 2, true);
//
//     //Рисуем квадрат
//     ctx.fillStyle = "rgba(91, 95, 201, 0.58)";
//     ctx.fillRect(5, 5, value_R, value_R);
//
//     //треугольник
//     ctx.moveTo(150, 70);
//     ctx.lineTo(175, 70);
//     ctx.lineTo(150, 20);
//     ctx.fill();
//     ctx.fillStyle = "black";
//     ctx.beginPath();
//
//     //линяя x
//     ctx.moveTo(150, 70);
//     ctx.lineTo(220, 70);
//
//     //стрелка
//     ctx.lineTo(215, 75);
//     ctx.moveTo(220, 70);
//     ctx.lineTo(215, 65);
//
//     ctx.fillText('X', 220, 65);
//     ctx.moveTo(150, 70);
//     ctx.lineTo(80, 70);
//
//     //значения X
//     ctx.moveTo(175, 75);
//     ctx.lineTo(175, 65);
//     ctx.fillText(value_R / 2, 170, 63);
//     ctx.moveTo(200, 75);
//     ctx.lineTo(200, 65);
//     ctx.fillText(value_R, 197, 63);
//
//     ctx.moveTo(125, 75);
//     ctx.lineTo(125, 65);
//     ctx.fillText(-1 * value_R / 2, 114, 63);
//     ctx.moveTo(100, 75);
//     ctx.lineTo(100, 65);
//     ctx.fillText(-1 * value_R, 96, 63);
//
//     //леняя Y
//     ctx.moveTo(150, 70);
//     ctx.lineTo(150, 140);
//     ctx.moveTo(150, 70);
//     ctx.lineTo(150, 5);
//     //стрелка
//     ctx.lineTo(155, 10);
//     ctx.moveTo(150, 5);
//     ctx.lineTo(145, 10);
//     ctx.fillText('Y', 155, 15);
//
//     //значения X
//     ctx.moveTo(145, 95);
//     ctx.lineTo(155, 95);
//     ctx.fillText(-1 * value_R / 2, 160, 100);
//     ctx.moveTo(145, 120);
//     ctx.lineTo(155, 120);
//     ctx.fillText(-1 * value_R, 160, 123);
//
//     ctx.moveTo(145, 45);
//     ctx.lineTo(155, 45);
//     ctx.fillText(value_R / 2, 160, 48);
//     ctx.moveTo(145, 20);
//     ctx.lineTo(155, 20);
//     ctx.fillText(value_R, 160, 25);
//
//     ctx.closePath();
//     ctx.stroke();
//
// }



















//     ctx.clearRect(0, 0, 1000, 1000);
//
//
//     //линяя x
//     ctx.moveTo(150,70);
//     ctx.lineTo(220,70);
//
//     //стрелка
//     ctx.lineTo(215,75);
//     ctx.moveTo(220,70);
//     ctx.lineTo(215,65);
//
//     ctx.fillText('X',220,65);
//     ctx.moveTo(150,70);
//     ctx.lineTo(80,70);
//
//
//     //леняя Y
//     ctx.moveTo(150,70);
//     ctx.lineTo(150,140);
//     ctx.moveTo(150,70);
//     ctx.lineTo(150,5);
//     //стрелка
//     ctx.lineTo(155,10);
//     ctx.moveTo(150,5);
//     ctx.lineTo(145,10);
//     ctx.fillText('Y',155,15);
//
//
//     //Рисуем квадрат
//     ctx.fillStyle = "rgba(91, 95, 201, 0.58)";
//     ctx.fillRect(0, 0, value_R, value_R);
//
//
//     //Рисуем прямоугольный треугольник
//     ctx.beginPath(); //начинаем новый путь
//     ctx.moveTo(0, value_R); //Переместить перо в точку (0, value_R)
//     ctx.lineTo(0, 0);  // Нарисовать линию к точке (0, 0)
//     ctx.lineTo(value_R, 0);
//     ctx.closePath();
//     ctx.fillStyle = "rgba(91, 95, 201, 0.58)";
//     ctx.fill();
//
//     // Рисуем сектор круга
//     ctx.beginPath();
//     ctx.moveTo(0, 0);
//     ctx.arc(0, 0, value_R / 2, Math.PI, Math.PI + Math.PI / 2, false);
//     ctx.closePath();
//     ctx.fillStyle = "rgba(91, 95, 201, 0.58)";
//     ctx.fill();
// }






