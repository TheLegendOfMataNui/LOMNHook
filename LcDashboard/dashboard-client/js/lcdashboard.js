//
// Litestone LcDashboard Web Client
//

const tableTreeElement = document.getElementById("tabletree");
const canvasElement = document.getElementById("canvas");

const apiIndexEndpoint = "/api/index";

var treeItems = { }; // Dictionary<string, TableTreeItem>
var tables = { }; // Dictionary<string, Table>
var selectedTreeItem = null; // TableTreeItem

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
        // Remove the selected class
        selectedTreeItem.label.classList.remove("selected");
    }
    selectedTreeItem = item;
    item.label.classList.add("selected");
}

function getOrAddTableTreeItem(name) {
    if (name in treeItems)
        return treeItems[name];
    
    let segments = name.split("/");
    let newTableTreeItem = new TableTreeItem(segments[segments.length - 1]);
    treeItems[name] = newTableTreeItem;
    return newTableTreeItem;
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

            let item = null;// = getOrAddTableTreeItem(nameSoFar);
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
//rebuildTableTree(["a", "a2", "b", "c", "a2/q", "a2/z", "a2/w", "a2/z/2500"]);