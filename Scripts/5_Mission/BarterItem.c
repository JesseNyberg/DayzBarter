class BarterItem {
	string id;
	string category;
    ref array<ref FinalItem> finalProducts;
    ref array<ref RequiredItem> requiredItems;
	
}

class RequiredItem {
	string itemName;
	int quantity;
}

class FinalItem {
	string itemName;
	int quantity;
}