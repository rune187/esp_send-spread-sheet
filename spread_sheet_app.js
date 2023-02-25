function doGet(e) {

    /**
     * sheeturls Random ID of "＊＊＊＊＊" part ↓
     * https://docs.google.com/spreadsheets/d/＊＊＊＊＊/edit#gid=0
     */
    let id = '';
    /**
     * sheetname
     * default: シート1
     */
    let sheetName = 'temp_log';
    var result;

    // e.parameter has received GET parameters, i.e. temp, humi
    if (e.parameter == undefined) {
        result = 'Parameter undefined';
    } else {
        var sheet = SpreadsheetApp.openById(id).getSheetByName(sheetName);
        var newRow = sheet.getLastRow() + 1;  // get row number to be inserted
        var rowData = [];

        // get current time
        const date = new Date()
        const dateTime = date.getFullYear() + '/' + (date.getMonth()+1) + '/' + date.getDate() + ' ' + date.getHours() + ':' + date.getMinutes() + ':' + date.getSeconds();
        rowData[0] = dateTime;
        rowData[1] = e.parameter.temp;
        rowData[2] = e.parameter.humi;

        // 1 x rowData.length cells from (newRow, 1) cell are specified
        var newRange = sheet.getRange(newRow, 1, 1, rowData.length);

        // insert data to the target cells
        newRange.setValues([rowData]);
        result =  'post';
    }

    return ContentService.createTextOutput(result);
}