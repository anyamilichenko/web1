let cookies_data="";


//getData - асинхронный GET-запрос на сервер
function getData(){
    const xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function (){
        if (xhr.readyState === XMLHttpRequest.DONE){
            if (Cookies.get('input_data') !== undefined){
                cookies_data = Cookies.get('input_data');
            }
            cookies_data += php_response(xhr.responseText);
            Cookies.set("input_data", cookies_data);
            addToTable();
        }
    }
    xhr.open('POST', 'server.php?'+'x='+val_x+'&y='+val_y+'&r='+value_R,);
    xhr.send();
}

function php_response(param){
    if (param.split("/")[0].split(";")[0] == "false"){
        alert("Отправляемые данные ошибочны");
    }else{
        // drawPoint(val_x * 10, val_y * 10, value_R * 10);
        return param;
    }
}

