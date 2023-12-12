class BarterItem {
	string id;
	string category;
    string finalProduct;
    ref array<string> requiredItems;
	
	void BarterItem(string identity, string cat, string finalProd, ref array<string> reqItems) {
		id = identity;
        category = cat;
        finalProduct = finalProd;
        requiredItems = reqItems;
    }
}