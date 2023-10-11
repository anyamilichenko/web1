function addToTable(){
    let table = document.getElementById("table_out")
    let data = Cookies.get("input_data")
    let input = "";

    if (data !== undefined && data !== "") {
        let arr_data = data.split("/");
        for (let i = 0; i < arr_data.length - 1; i++) {
            let data_value = arr_data[i].split(";");
            input = input + "<tr>"
            for (let j = 1; j < data_value.length; j++) {
                input += "<td>"
                input += data_value[j]
                input += "</td>"
            }
            input += "</tr>"
        }
        table.innerHTML = input; // позволяет считать содержимое элемента в виде HTML-строки или установить новый HTML
    }
}
addToTable();

