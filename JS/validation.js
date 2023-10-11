let input = document.getElementById("Y");
let val_x = 0;
let val_y = 3;
let flag = true;


function set_x(){
    val_x = document.getElementById("X").options[document.getElementById("X").options.selectedIndex].value;
    document.getElementById('label_x').innerText = "X = " + val_x;
}
function check_input(){
    val_y = input.value.trim().replace(",", ".");
    if (val_y === ""){
        alert("Значение \"Y\" не валидно");
        input.value = "";
        flag = false;
    }else if (!isFinite(+val_y)){
        alert("Значение должно быть числом");
        input.value = "";
        flag = false;
    }else if(val_y <= -3 || val_y >= 5){
        alert("Значение должно входить в диапазон (-3; 5)");
        input.value = "";
        flag = false;


    }else{
        val_y = input.value.replace(/,/,".");
        document.getElementById('label_y').innerText = "Y = " + input.value;
        flag = true;
    }
}

let button = document.getElementById("button");

button.onclick = function() {
    check_input();
    if (flag) {
        getData();
    }
}
// // Функция для очистки таблицы
//     function clearTable() {
//         let table = document.getElementById("table_out");
//         table.innerHTML = ""; // Очищаем содержимое таблицы
//     }
// // Вызываем функцию при клике на кнопку "Очистить таблицу"
//     document.getElementById("clearButton").addEventListener("click", clearTable);
// }