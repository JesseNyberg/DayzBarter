class BarterUI : UIScriptedMenu
{
	private Widget rootLayout;
	private GridSpacerWidget barterGridSpacer;
	private GridSpacerWidget recipeGridSpacer;
	private GridSpacerWidget finalProductGridSpacer;
	
	private GridSpacerWidget finalTextGridSpacer;
	private GridSpacerWidget textGridSpacer;
	private GridSpacerWidget previewTextGridSpacer;
	
	private GridSpacerWidget finalQuantityGridSpacer;
	private GridSpacerWidget previewQuantityGridSpacer;
	
	private ButtonWidget m_escapeButton;
	private ButtonWidget m_buyButton;
	private ButtonWidget m_buttonWidget;
	
	private ItemPreviewWidget m_recipePreview1;
	private ItemPreviewWidget m_recipePreview2;
	private ItemPreviewWidget m_itemPreviewWidget;
	private ItemPreviewWidget m_recipePreviewWidget;
	private ItemPreviewWidget m_finalProductWidget;
	
	private TextWidget m_selectedName;
	private TextWidget m_textPlus;
	private TextWidget m_barterLevelText;
	private TextWidget m_buyText;
	private TextWidget m_textWidget;
	private TextWidget m_arrowText;
	
	private XComboBoxWidget m_categoryWidget;
	
	private bool isItemSelected = false;
	
	private ImageWidget m_backgroundImage;
	
	private PlayerBase player;
	
	private ref array<ButtonWidget> m_checkedButtons;
	
	private ref array<string> m_uniqueCategories;

	
	private ref array<ItemPreviewWidget> m_itemPreviews;
	private ref array<ItemPreviewWidget> m_recipePreviews;
	private ref array<ItemPreviewWidget> m_finalPreviews;
	
	private ref BartererList bartererList;
	private ref BarterItem selectedBarterItem;
	private ref array<ref BarterItem> m_barterItems;
	
	private int MAX_RECIPE_ITEMS = 16;
	
	void BarterUI()
	{
		m_checkedButtons = new array<ButtonWidget>;
		
		m_itemPreviews = new array<ItemPreviewWidget>;
		m_recipePreviews = new array<ItemPreviewWidget>;
		m_finalPreviews = new array<ItemPreviewWidget>;
		
		m_barterItems = new array<ref BarterItem>;
		
		GetRPCManager().AddRPC("BarterMod", "RPCReceiveBartererList", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("BarterMod", "RPCUpdateLevelText", this, SingleplayerExecutionType.Client);
	}
	
	void RequestBartererListFromServer() {
		GetRPCManager().SendRPC("BarterMod", "RespondBartererList", new Param1<PlayerIdentity>(GetGame().GetPlayer().GetIdentity()));
    }
	
	void RPCReceiveBartererList(CallType callType, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
        if (callType == CallType.Client) {
            Param1<ref BartererList> param;
            if (!ctx.Read(param)) return;

            bartererList = param.param1;
			
			
			populateCategories();
        }
    }
	
	void RPCUpdateLevelText(CallType callType, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
        if (callType == CallType.Client) {
            Param1<int> data;
            if (!ctx.Read(data)) return;

            int newBarterLevel = data.param1;
            m_barterLevelText.SetText("Barter level: " + newBarterLevel.ToString());
        }
    }
	
	void populateCategories() {
		m_uniqueCategories = new array<string>;
		m_categoryWidget.ClearAll();

		foreach (Barterer barterer : bartererList.barterers) {
			if (barterer.npcID == TARGETED_TRADER_NPC) {
				foreach (BarterItem barterItem : barterer.items) {
					if (m_uniqueCategories.Find(barterItem.category) == -1) {
						m_uniqueCategories.Insert(barterItem.category);
						m_categoryWidget.AddItem(barterItem.category); 
					}
				}
			}
		}
		populateEntities();
	}
		
	override Widget Init()
	{
		RequestBartererListFromServer();
		
		if (!rootLayout)
		{
			rootLayout = GetGame().GetWorkspace().CreateWidgets("DayzBarter/Scripts/layouts/BarterMenu.layout");
			
			if (rootLayout)
			{
				barterGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerPreviews"));
				recipeGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerRecipes"));
				finalProductGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerFinalProduct"));
				
				textGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerText"));
				previewTextGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerPreviewText"));
				finalTextGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerFinalText"));
				
				previewQuantityGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerPreviewQuantity"));
				finalQuantityGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerFinalQuantity"));
				
				
				m_escapeButton = ButtonWidget.Cast(rootLayout.FindAnyWidget("escapeButton"));
				m_buyButton = ButtonWidget.Cast(rootLayout.FindAnyWidget("buyButton"));
				
				m_selectedName = TextWidget.Cast(rootLayout.FindAnyWidget("selectedName"));
				m_buyText = TextWidget.Cast(rootLayout.FindAnyWidget("buyText"));
				m_barterLevelText = TextWidget.Cast(rootLayout.FindAnyWidget("barterLevelText"));
				m_arrowText = TextWidget.Cast(rootLayout.FindAnyWidget("arrowText"));
				
				m_categoryWidget = XComboBoxWidget.Cast(rootLayout.FindAnyWidget("categoryWidget"));
				
				m_backgroundImage = ImageWidget.Cast(rootLayout.FindAnyWidget("ImageWidget0"));
				m_backgroundImage.LoadImageFile(0, "DayzBarter/barterbackground.edds");
				m_backgroundImage.SetImage(0);
				

				player = PlayerBase.Cast(GetGame().GetPlayer());
				

				
			} else {
				Print("BARTER: Failed to create root widget.");
			}
		}
		return rootLayout;
	}
	
	override void OnShow()
	{
		super.OnShow();
		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetMission().PlayerControlEnable(false);
		GetGame().GetMission().GetHud().Show(false);
		
		setBarterLevelText();
		
		player.setBarterMenuOpen(true);
		
		if (rootLayout) {
			SetFocus(rootLayout);
		}
	}
	
	override void OnHide()
	{
		super.OnHide();
		
		GetGame().GetUIManager().ShowCursor(false);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().PlayerControlEnable(true);
		GetGame().GetMission().GetHud().Show(true);
		
		player.setBarterMenuOpen(false);
		
		if (rootLayout)
			rootLayout.Unlink();
	}
	
	void setBarterLevelText() {
		m_barterLevelText.SetText("Barter level: " + player.getBarterLevel().ToString());
	}
	
	ButtonWidget GetButtonWidget( string name ) 
	{
		foreach( ButtonWidget widget : m_checkedButtons ) 
		{
			if ( widget.GetName() == name ) 
			{
				return widget;
			}
		}
		return null;
	}
	
	EntityAI createEntity(string entityName) {
		EntityAI entity = EntityAI.Cast(GetGame().CreateObject(entityName, "0 0 0", true, false, true));
		return entity;
	}
	
	void showTradePreviews(bool showBoolean) {
		recipeGridSpacer.Show(showBoolean);
		finalProductGridSpacer.Show(showBoolean);
		
		m_buyButton.Show(showBoolean);
		m_buyText.Show(showBoolean);
	}
	
	void ClearGridSpacer(GridSpacerWidget grid) {
		if (!grid) {
			return;
		}

		Widget child = grid.GetChildren();
		while (child) {
			Widget next = child.GetSibling();
			
			if (child.IsInherited(ItemPreviewWidget)) {
				delete child; 
			}
			
			child = next;
		}
	}
	
	void clearPreviousRecipeTexts(string textWidgets) {
		for (int i = 0; i < MAX_RECIPE_ITEMS; i++) { 
			TextWidget textWidget = TextWidget.Cast(rootLayout.FindAnyWidget(textWidgets + i.ToString()));
			if (textWidget) {
				textWidget.SetText(""); 
			}
		}
	}
	
	void setPreviewItems(string id) {
		ClearGridSpacer(recipeGridSpacer);
		ClearGridSpacer(finalProductGridSpacer);
		
		clearPreviousRecipeTexts("textRecipePreview");
		clearPreviousRecipeTexts("textRecipeQuantity");
		clearPreviousRecipeTexts("textFinalText");
		clearPreviousRecipeTexts("textFinalQuantity");
		
		foreach (BarterItem barterItem : m_barterItems) {
			if (barterItem.id == id) {
				selectedBarterItem = barterItem;
				
				int i = 0;
				
				foreach (FinalItem finalItem : selectedBarterItem.finalProducts) {
					EntityAI finalEntity = createEntity(finalItem.itemName);
					
					if (finalEntity) {
						m_finalProductWidget = createItemPreview(finalProductGridSpacer);
						m_finalProductWidget.SetItem(finalEntity);
						
						m_textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textFinalText" + i.ToString()));
						m_textWidget.SetText(finalEntity.GetDisplayName());
						
						m_textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textFinalQuantity" + i.ToString()));
						if (finalItem.quantity > 1) m_textWidget.SetText(finalItem.quantity.ToString());
						
						i++;
					}
				}
				
				int j = 0;
				
				foreach (RequiredItem requiredItem : selectedBarterItem.requiredItems) {
					EntityAI recipeEntity = createEntity(requiredItem.itemName);
					
					if (recipeEntity) {
						m_recipePreviewWidget = createItemPreview(recipeGridSpacer);
						m_recipePreviewWidget.SetItem(recipeEntity);
						
						m_textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textRecipePreview" + j.ToString()));
						m_textWidget.SetText(recipeEntity.GetDisplayName());
						
						m_textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textRecipeQuantity" + j.ToString()));
						if (requiredItem.quantity > 1) m_textWidget.SetText(requiredItem.quantity.ToString());
						
						j++;
					}
				}
				showTradePreviews(true);
				return; 
			}
		}
		showTradePreviews(false); 
	}


	void setTradeInfo(Widget w) {
		isItemSelected = true;
		
		ButtonWidget selectedButton = GetButtonWidget(w.GetName());
			
		ItemPreviewWidget itemPreviewWidget = ItemPreviewWidget.Cast(selectedButton.GetParent());
			
		if (itemPreviewWidget)
		{
			EntityAI item = itemPreviewWidget.GetItem();
			if (item)
			{
				string itemName = item.GetDisplayName(); 
					
				m_selectedName.SetText(itemName); 
				setPreviewItems(w.GetName());
			}
		}
		
	}
		
	override bool OnClick(Widget w, int x, int y, int button)
	{
		
		if (w == m_escapeButton)
		{
			Close();
			return true;
		}
		
		if (w.IsInherited(ButtonWidget) && GetButtonWidget(w.GetName()))
		{
			setTradeInfo(w);
		} else {
			Print("BARTER: ButtonWidget not found!");
		}
		
		if (w.IsInherited(ButtonWidget) && w.GetName() == "buyButton") {
			
            if (player && isItemSelected && selectedBarterItem != null) {
                GetRPCManager().SendRPC("BarterMod", "RPCBuy", new Param2<PlayerBase, BarterItem>(player, selectedBarterItem));
            } else {
				ExpansionNotification("Barter", "You have to select an item first!").Error(player.GetIdentity());
			}
		}
		
		if (w == m_categoryWidget) {
			ClearGridSpacer(recipeGridSpacer);
			ClearGridSpacer(barterGridSpacer);
			ClearGridSpacer(finalProductGridSpacer);
			

			clearPreviousRecipeTexts("textRecipe");
			clearPreviousRecipeTexts("textRecipePreview");
			clearPreviousRecipeTexts("textRecipeQuantity");
			
			clearPreviousRecipeTexts("textFinalText");
			clearPreviousRecipeTexts("textFinalQuantity");
			
			m_selectedName.SetText(""); 
			
			isItemSelected = false;
			populateEntities();
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void populateEntities() {
		m_barterItems.Clear();
		
		if (!bartererList) {
			Print("BARTER: Barterer list not initialized correctly");
			return;
		}
		
		int currentCategoryIndex = m_categoryWidget.GetCurrentItem();
		string currentCategory = m_uniqueCategories.Get(currentCategoryIndex);
		
		Print("BARTER: NPC TARGETED " + TARGETED_TRADER_NPC);
		
		foreach (Barterer barterer : bartererList.barterers) {
			if (barterer.npcID == TARGETED_TRADER_NPC) {
				foreach (BarterItem barterItem : barterer.items) {
					if (currentCategory == barterItem.category) {
						m_barterItems.Insert(barterItem); 
					}
				}
			}
		}
		
		PopulateItems();
	}	
	
	ItemPreviewWidget createItemPreview(Widget parent) {
		ItemPreviewWidget itemPreview = ItemPreviewWidget.Cast(GetGame().GetWorkspace().CreateWidget(ItemPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE | WidgetFlags.IGNOREPOINTER | WidgetFlags.CLIPCHILDREN, ARGB(255, 255, 255, 255), 0, parent));
		return itemPreview;
	}
	
	ButtonWidget createButton(Widget parent) {
		ButtonWidget button = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidget(ButtonWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 0, parent));
		return button;
	}
	
	void PopulateItems()
	{
		if (!GetGame().IsClient() && GetGame().IsMultiplayer())
		{
			return;
		}
		int i = 0;
		m_checkedButtons.Clear();
		ClearGridSpacer(barterGridSpacer);
		
		foreach (BarterItem barterItem : m_barterItems)
		{
			string finalProductString = barterItem.finalProducts.Get(0).itemName;
			EntityAI finalProduct = createEntity(finalProductString);
			
			if (finalProduct) {
				m_itemPreviewWidget = createItemPreview(barterGridSpacer);
				
				m_buttonWidget = createButton(m_itemPreviewWidget);
				m_buttonWidget.ClearFlags(WidgetFlags.IGNOREPOINTER);
				m_buttonWidget.SetName(barterItem.id);
				
				m_textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textRecipe" + i.ToString()));
				m_textWidget.SetText(finalProduct.GetDisplayName());
				
				m_checkedButtons.Insert(m_buttonWidget);
				
				m_itemPreviewWidget.SetItem(finalProduct);
				m_itemPreviews.Insert(m_itemPreviewWidget);
				
				i++;
			} else {
				Print("BARTER: Failed to create entity for " + finalProductString);
			}
		}
	}
}
