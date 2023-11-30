class BarterUI : UIScriptedMenu
{
	private Widget rootLayout;
	private GridSpacerWidget barterGridSpacer;
	private GridSpacerWidget recipeGridSpacer;
	private GridSpacerWidget textGridSpacer;
	private GridSpacerWidget previewTextGridSpacer;
	
	private ButtonWidget m_escapeButton;
	private ButtonWidget m_buyButton;
	private ButtonWidget m_buttonWidget;
	
	private ItemPreviewWidget m_recipePreview1;
	private ItemPreviewWidget m_recipePreview2;
	private ItemPreviewWidget m_tradablePreview;
	private ItemPreviewWidget m_itemPreviewWidget;
	private ItemPreviewWidget m_recipePreviewWidget;
	
	private TextWidget m_selectedName;
	private TextWidget m_textPlus;
	private TextWidget m_textEqual;
	private TextWidget m_barterLevelText;
	private TextWidget m_buyText;
	
	private TextWidget m_textWidget;
	private bool isItemSelected = false;
	

	
	private ImageWidget m_backgroundImage;
	
	private PlayerBase player;
	
	private ref array<EntityAI> m_itemEntities;
	private ref array<ButtonWidget> m_checkedButtons;
	private ref map<string, ref array<EntityAI>> m_entityMap;
	
	private ref array<ItemPreviewWidget> m_itemPreviews;
	private ref array<ItemPreviewWidget> m_recipePreviews;
	private ref array<TextWidget> m_t
	private ref array<EntityAI> m_recipeEntities;
	private ref array<string> m_recipeStrings;
	private ref BartererList bartererList;
	
	private int MAX_RECIPE_ITEMS = 16;
	
	void BarterUI()
	{
		
		m_checkedButtons = new array<ButtonWidget>;
		m_itemPreviews = new array<ItemPreviewWidget>;
		m_itemEntities = new array<EntityAI>;
		
		m_recipePreviews = new array<ItemPreviewWidget>;
		m_recipeEntities = new array<EntityAI>;
		m_recipeStrings = new array<string>;
		m_entityMap = new map<string, ref array<EntityAI>>;
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
			populateEntities();
        }
    }
	
	void RPCUpdateLevelText(CallType callType, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
        if (callType == CallType.Client) {
            Param1<int> data;
            if (!ctx.Read(data)) return;

            int newSkillLevel = data.param1;
            m_barterLevelText.SetText("Barter level: " + newSkillLevel.ToString());
        }
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
				textGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerText"));
				recipeGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerRecipes"));
				previewTextGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerPreviewText"));
				
				m_escapeButton = ButtonWidget.Cast(rootLayout.FindAnyWidget("escapeButton"));
				m_buyButton = ButtonWidget.Cast(rootLayout.FindAnyWidget("buyButton"));
				
				m_tradablePreview = ItemPreviewWidget.Cast(rootLayout.FindAnyWidget("tradablePreview"));
				
				m_selectedName = TextWidget.Cast(rootLayout.FindAnyWidget("selectedName"));
				m_buyText = TextWidget.Cast(rootLayout.FindAnyWidget("buyText"));
				m_textEqual = TextWidget.Cast(rootLayout.FindAnyWidget("textEqual"));
				m_barterLevelText = TextWidget.Cast(rootLayout.FindAnyWidget("barterLevelText"));
				
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
		//PPEffects.SetBlurMenu(0.5);
		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetMission().PlayerControlEnable(false);
		GetGame().GetMission().GetHud().Show(false);
		
		setBarterLevelText();
		
		player.m_barterMenuOpen = true;
		
		if (rootLayout) {
			SetFocus(rootLayout);
		}
	}
	
	override void OnHide()
	{
		super.OnHide();
		//PPEffects.SetBlurMenu(0);
		
		GetGame().GetUIManager().ShowCursor(false);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().PlayerControlEnable(true);
		GetGame().GetMission().GetHud().Show(true);
		
		player.m_barterMenuOpen = false;
		
		if (rootLayout)
			rootLayout.Unlink();
	}
	
	void setBarterLevelText() {
		m_barterLevelText.SetText("Barter level: " + player.m_currentSkillLevel.ToString());
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
		m_tradablePreview.Show(showBoolean);
		m_textEqual.Show(showBoolean);
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
	
	void clearPreviousRecipes() {
		m_recipeStrings.Clear();
		ClearGridSpacer(recipeGridSpacer);
		ClearGridSpacer(previewTextGridSpacer);
	}
	
	void clearPreviousRecipeTexts() {
		for (int i = 0; i < MAX_RECIPE_ITEMS; i++) { 
			TextWidget textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textRecipePreview" + i.ToString()));
			if (textWidget) {
				textWidget.SetText(""); 
			}
		}
	}
	
	void setPreviewItems(string itemClassName) {
		clearPreviousRecipes();
		clearPreviousRecipeTexts();

		if (m_entityMap.Contains(itemClassName)) {
			EntityAI finalProduct = createEntity(itemClassName);
			m_tradablePreview.SetItem(finalProduct);

			int i = 0;
			array<EntityAI> requiredItems = m_entityMap.Get(itemClassName);
			foreach (EntityAI recipeEntity : requiredItems) {
				if (recipeEntity) {
					m_recipePreviewWidget = createItemPreview(recipeGridSpacer);
					m_recipePreviewWidget.SetItem(recipeEntity);
					m_recipeStrings.Insert(recipeEntity.GetType());
					m_textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textRecipePreview" + i.ToString()));
					m_textWidget.SetText(recipeEntity.GetDisplayName());
					i++;
					//m_textWidget = createText(previewTextGridSpacer);
					//m_textWidget.SetText(recipeEntity.GetDisplayName());
				}
			}
			showTradePreviews(true);
		} else {
			showTradePreviews(false);
		}
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
				string itemClassName = item.GetType();
					
				m_selectedName.SetText(itemName); 
				setPreviewItems(itemClassName);
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
			EntityAI finalProduct = m_tradablePreview.GetItem();
			
            if (player && isItemSelected) {
                GetRPCManager().SendRPC("BarterMod", "RPCBuy", new Param3<PlayerBase, array<string>, string>(player, m_recipeStrings, finalProduct.GetType()));
            } else {
				ExpansionNotification("Barter", "You have to select an item first!").Error(player.GetIdentity());
			}
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void populateEntities() {
		
		if (!bartererList) {
			Print("BARTER: Barterer list not initialized correctly");
			return;
		}
		
		foreach (Barterer barterer : bartererList.barterers) {
			
			if (barterer.npc == TARGETED_TRADER_NPC) {
				foreach (BarterItem barterItem : barterer.items) {
					ref array<EntityAI> requiredItems = new array<EntityAI>;

					foreach (string requiredItem : barterItem.requiredItems) {
						EntityAI recipeEntity = createEntity(requiredItem);
						requiredItems.Insert(recipeEntity);
					}
					
					m_entityMap.Insert(barterItem.finalProduct, requiredItems);
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
	
	RichTextWidget createText(Widget parent) {
		RichTextWidget text = RichTextWidget.Cast(GetGame().GetWorkspace().CreateWidget(RichTextWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE | WidgetFlags.IGNOREPOINTER, ARGB(255, 255, 255, 255), 0, parent));
		return text;
	}
	
	
	
	void PopulateItems()
	{
		if (!GetGame().IsClient() && GetGame().IsMultiplayer())
		{
			return;
		}
		int i = 0;
		
		foreach (string finalProductString, array<EntityAI> requiredItems : m_entityMap)
		{
			EntityAI finalProduct = createEntity(finalProductString);
			
			if (finalProduct) {
				m_itemPreviewWidget = createItemPreview(barterGridSpacer);
				
				m_buttonWidget = createButton(m_itemPreviewWidget);
				m_buttonWidget.ClearFlags(WidgetFlags.IGNOREPOINTER);
				m_buttonWidget.SetName("Button_" + finalProduct.GetDisplayName());
				
				m_textWidget = TextWidget.Cast(rootLayout.FindAnyWidget("textRecipe" + i.ToString()));
				m_textWidget.SetText(finalProduct.GetDisplayName());
				i++;
				// m_textWidget = createText(textGridSpacer);
				// m_textWidget.SetText(finalProduct.GetDisplayName());
				// m_textWidget.SetFlags(WidgetFlags.EXACTSIZE);
				// m_textWidget.SetTextExactSize(12);
				
				m_checkedButtons.Insert(m_buttonWidget);
				
				m_itemPreviewWidget.SetItem(finalProduct);
				m_itemPreviews.Insert(m_itemPreviewWidget);
				
			} else {
				Print("BARTER: Failed to create entity for " + finalProductString);
			}
		}
	}
}
