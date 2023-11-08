class BarterUI : UIScriptedMenu
{
	private Widget rootLayout;
	private GridSpacerWidget barterGridSpacer;
	private GridSpacerWidget recipeGridSpacer;
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
	private TextWidget m_traderTitle;
	private TextWidget m_barterLevelText;
	private TextWidget m_buyText;
	
	private ImageWidget m_backgroundImage;
	
	private PlayerBase player;
	
	private ref array<EntityAI> m_itemEntities;
	private ref array<ButtonWidget> m_checkedButtons;
	
	private ref array<ItemPreviewWidget> m_itemPreviews;
	private ref array<ItemPreviewWidget> m_recipePreviews;
	private ref array<EntityAI> m_recipeEntities;
	private ref array<string> m_recipeStrings;
	
	void BarterUI()
	{
		
		m_checkedButtons = new array<ButtonWidget>;
		m_itemPreviews = new array<ItemPreviewWidget>;
		m_itemEntities = new array<EntityAI>;
		
		m_recipePreviews = new array<ItemPreviewWidget>;
		m_recipeEntities = new array<EntityAI>;
		m_recipeStrings = new array<string>;
	}
		
	override Widget Init()
	{
		if (!rootLayout)
		{
			rootLayout = GetGame().GetWorkspace().CreateWidgets("DayzBarter/Scripts/layouts/BarterMenu.layout");
			
			if (rootLayout)
			{
				Print("BARTER: Root Widget created");
				barterGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerPreviews"));
				recipeGridSpacer = GridSpacerWidget.Cast(rootLayout.FindAnyWidget("GridSpacerRecipes"));
				
				m_escapeButton = ButtonWidget.Cast(rootLayout.FindAnyWidget("escapeButton"));
				m_buyButton = ButtonWidget.Cast(rootLayout.FindAnyWidget("buyButton"));
				
				m_tradablePreview = ItemPreviewWidget.Cast(rootLayout.FindAnyWidget("tradablePreview"));
				
				m_selectedName = TextWidget.Cast(rootLayout.FindAnyWidget("selectedName"));
				m_buyText = TextWidget.Cast(rootLayout.FindAnyWidget("buyText"));
				m_textEqual = TextWidget.Cast(rootLayout.FindAnyWidget("textEqual"));
				//m_traderTitle = TextWidget.Cast(rootLayout.FindAnyWidget("traderTitle"));
				m_barterLevelText = TextWidget.Cast(rootLayout.FindAnyWidget("barterLevelText"));
				
				m_backgroundImage = ImageWidget.Cast(rootLayout.FindAnyWidget("ImageWidget0"));
				m_backgroundImage.LoadImageFile(0, "DayzBarter/barterbackground.edds");
				m_backgroundImage.SetImage(0);
				
				player = PlayerBase.Cast(GetGame().GetPlayer());
				
				populateEntities();

				
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
		
		if (rootLayout) {
			SetFocus(rootLayout);
		}
	}
	
	override void OnHide()
	{
		super.OnHide();
		//PPEffects.SetBlurMenu(0);
		Print("OnHide triggered");
		
		GetGame().GetUIManager().ShowCursor(false);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().PlayerControlEnable(true);
		GetGame().GetMission().GetHud().Show(true);
		
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
			
			// If you only want to remove ItemPreviewWidgets, check for them
			if (child.IsInherited(ItemPreviewWidget)) {
				delete child; // This should remove the widget
			}
			
			child = next;
		}
	}
	
	void clearPreviousRecipes() {
		m_recipePreviews.Clear();
		m_recipeEntities.Clear();
		m_recipeStrings.Clear();
		ClearGridSpacer(recipeGridSpacer);
	}
	
	void setPreviewItems(string itemClassName) {
		
		switch (TARGETED_TRADER_NPC) {
			
			//////////////////////////////////////////////
			case "SurvivorM_Denis":
			
				switch (itemClassName) {
					
					case "M4A1":
					
						clearPreviousRecipes();
						m_recipeEntities.Insert(createEntity("SKS"));
						m_recipeEntities.Insert(createEntity("Deagle"));
						
						foreach (EntityAI item : m_recipeEntities) {
							m_recipePreviewWidget = createItemPreview(recipeGridSpacer);
							m_recipePreviewWidget.SetItem(item);
							m_recipeStrings.Insert(item.GetType());
						}
						
						m_tradablePreview.SetItem(createEntity("M4A1"));
						showTradePreviews(true);
						break;
						
					default:
						clearPreviousRecipes();
						showTradePreviews(false);
						break;
						
				}
				break;
			////////////////////////////////////////////	
			
			////////////////////////////////////////////
			case "SurvivorM_Elias":
			
				switch (itemClassName) {
					case "SantasHat":
						clearPreviousRecipes();
						showTradePreviews(true);
						break;
						
					default:
						clearPreviousRecipes();
						showTradePreviews(false);
						break;
				}
				break;
			//////////////////////////////////////////
			
			default:
				break;
		}
	}
	
	void setTradeInfo(Widget w) {
		Print("BARTER: Button widget is being searched");
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
		Print("BARTER: OnClick triggered");
		
		if (w == m_escapeButton)
		{
			Print("BARTER: Escape button triggered");
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
			
            if (player) {
				Print("BARTER: If player before RPC");
				
				
                GetRPCManager().SendRPC("BarterMod", "RPCBuy", new Param3<PlayerBase, array<string>, string>(player, m_recipeStrings, finalProduct.GetType()));
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(setBarterLevelText, 3000, false, player);
            }
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	// Traderin tavaroiden lisäys
	// createEntity("TÄMÄ TYPES.XML NIMESTÄ") <type name="GhillieTop_Mossy"> esim
	// KOPIOI m_itementities.insert lauseita niin monta kuin tarvii traderin listaan tavaroita myyntiin
	void populateEntities() {
		
		switch (TARGETED_TRADER_NPC) {
			case "SurvivorM_Denis":
				//m_traderTitle.SetText("Roope K.");
				m_itemEntities.Insert(createEntity("Aug"));
				m_itemEntities.Insert(createEntity("AK101"));
				m_itemEntities.Insert(createEntity("M4A1"));
				break;
				
			case "SurvivorM_Elias":
				//m_traderTitle.SetText("Elias M.");
				m_itemEntities.Insert(createEntity("SeaChest"));
				m_itemEntities.Insert(createEntity("Hedgehog_Kit"));
				m_itemEntities.Insert(createEntity("CodeLock"));
				m_itemEntities.Insert(createEntity("SantasHat"));
				break;
				

			default:
				
				break;
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
		
		int maxColumns = 4;
		int maxRows = 4;
		int maxItems = maxColumns * maxRows;
		int currentItemCount = 0;

		foreach (EntityAI item: m_itemEntities)
		{
			m_itemPreviewWidget = createItemPreview(barterGridSpacer);
			
			m_buttonWidget = createButton(m_itemPreviewWidget);
			
			m_buttonWidget.ClearFlags(WidgetFlags.IGNOREPOINTER);
			m_buttonWidget.SetName("Button_" + item.GetDisplayName());
			m_checkedButtons.Insert(m_buttonWidget);
			
			m_itemPreviewWidget.SetItem(item);
			m_itemPreviews.Insert(m_itemPreviewWidget);

			currentItemCount++;
		}
	}
}
