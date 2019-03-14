//
// Litestone LcDashboard Web Client
//

const tableTreeElement = document.getElementById("tabletree");
const canvasElement = document.getElementById("canvas");

const apiIndexEndpoint = "/api/index";
const apiTableEndpoint = "/api/table";
const widgetTypes = { label: {create: labelContentCreate, update: labelContentUpdate} };

var treeItems = { }; // Dictionary<string, TableTreeItem>
var selectedTreeItem = null; // TableTreeItem
var currentTableContents = null; // TableContentsControl
var loadedTables = { }; // Dictionary<string, Table>

function labelContentCreate(widgetData) {

}

function labelContentUpdate(contentElement, widgetData) {

}

function placeWidgetControl(control, row, column) {
    control.row = row;
    control.column = column;
    // TODO: Set CSS grid & column with inline style
}

function buildWidgetElement(name, contentElement) {
    let label = document.createElement("DIV");
    label.className = "widget-label";
    label.appendChild(document.createTextNode(name));
    
    let content = document.createElement("DIV");
    content.className = "widget-content";
    content.appendChild(contentElement);

    let widget = document.createElement("DIV");
    widget.className = "widget";
    widget.appendChild(label);
    widget.appendChild(content);
    return widget;
}

//
// WidgetControl: A single widget in the UI. Takes its data from a WidgetInfo.
//
function WidgetControl(widgetInfo, row, column) {
    this.info = widgetInfo;
    this.info.controls.push(this);
    this.contentElement = this.info.type.create(this.info.data);
    this.element = buildWidgetElement(this.info.name, this.contentElement);
    this.row = row;
    this.column = column;
    placeWidgetControl(this, row, column);
}

//
// TableContentsControl
//
function TableContentsControl() {
    this.widgets = []; // WidgetControl[]
    this.element = document.createElement("DIV");
    this.element.className = "table-contents";
    this.widgetCount = 0;
}

//
// WidgetInfo: Stores the data for a single widget.
//
function WidgetInfo(name, typeName, data) {
    this.name = name;
    this.typeName = typeName;
    this.type = widgetTypes[typeName];
    this.data = data;
    this.controls = []; // WidgetControl[]
}

//
// TableInfo: Stores the data for a table and the contained widgets.
//
function TableInfo(name) {
    this.name = name;
    this.widgets = { }; // Map<string, Widget>
    this.controls = []; // TableContentsControl[]
}

function loadTableData(table) {
    fetch(apiTableEndpoint + "/" + table.name).then(function(response) {
        return response.json();
    }).then(function(json) {
        if (json.success) {
            let oldWidgets = table.widgets;
            table.widgets = { };
            for (let i = 0; i < json.data.widgets.length; i++) {
                let widgetData = json.data.widgets[i];
                let widget = null;
                if (widgetData.name in oldWidgets) {
                    // Update existing widget
                    widget = oldWidgets[widgetData.name];
                    delete oldWidgets[widgetData.name];
                }
                else {
                    // Create new widget
                    widget = new WidgetControl(widgetData);
                }

            }

            for (let i = 0; i < oldWidgets.length; i++) {
                // Delete old widget

            }
        }
        else {
            console.log("API Failure loading table '" + table.name + "'!");
        }
    });
}

//
// TableTreeItem: An item in the table tree. Not necessarily a table.
//
function TableTreeItem(name) {
    this.name = name;
    this.tableName = null;
    this.childItems = []; // List<TableTreeItem>
    this.table = null;
    this.element = document.createElement("DIV");
    this.element.className = "tree-item";
    this.label = document.createElement("DIV");
    this.label.appendChild(document.createTextNode(name));
    this.label.className = "tree-item-label";
    this.element.appendChild(this.label);
    this.children = document.createElement("DIV");
    this.children.className = "tree-item-children";
    this.element.appendChild(this.children);
    let thisTreeItem = this;
    console.log("Creating TableTreeItem '" + name + "'.");
    this.label.addEventListener("click", function() {
        selectTableTreeItem(thisTreeItem);
    });
}

function selectTableTreeItem(item) {
    if (selectedTreeItem != null) {
        selectedTreeItem.label.classList.remove("selected");
    }
    selectedTreeItem = item;
    item.label.classList.add("selected");

    // TODO: Delete old table contents
    for (let i = 0; i < )
    currentTableContents = new TableContentsControl();
}

function rebuildTableTree(tableNames) {
    treeItems = { };
    for (let i = 0; i < tableTreeElement.children.length; i++)
        tableTreeElement.children[i].remove();

    for (let n = 0; n < tableNames.length; n++) {
        let segments = tableNames[n].split("/");
        let nameSoFar = "";
        let parentItem = null;
        // TODO: Consider adding the root item to the DOM after building the sub-tree for perf improvements.
        for (let i = 0; i < segments.length; i++) {
            if (i > 0)
                nameSoFar += "/";
            nameSoFar += segments[i];

            let item = null;
            if (nameSoFar in treeItems) {
                item = treeItems[nameSoFar];
            }
            else {
                item = new TableTreeItem(segments[i]);
                treeItems[nameSoFar] = item;
                if (parentItem == null) {
                    tableTreeElement.appendChild(item.element);
                }
                else {
                    parentItem.children.appendChild(item.element);
                    parentItem.childItems.push(item);
                }
            }


            parentItem = item;

            if (selectedTreeItem == null)
                selectTableTreeItem(item);
        }
        parentItem.tableName = tableNames[n];
    }
}

function reloadTableTree() {
    fetch(apiIndexEndpoint).then(function(response) { 
        return response.json();
    }).then(function(json) {
        if (json.success) {
            rebuildTableTree(json.data.tables);
        }
        else {
            console.log("API Failure reloading table tree!");
        }
    });
}

function connect() {
    reloadTableTree();
}

connect();
