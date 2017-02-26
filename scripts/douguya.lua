-- 店員タイプごとの会話データ
talk_data = {
	-- 店員
	default = {
		welcome = "いらっしゃいませ！道具屋「ルア」へようこそ！",
		select = "何にするかい？",
		error = "え？何だって？",
		nomoney = "%s だね。でもお金が %d円足りないみたいだね。" ..
				"またおいで\n",
		success = "%s だね。じゃあ %d円いただくよ。\n",
		bye = "またいらっしゃい！",
	},
	-- 女性店員
	woman = {
		welcome = "こんにちわ！道具屋「ルア」へようこそ！",
		select = "何にいたしますか？",
		error = "え？何でしょう？",
		nomoney = "%s ですね。でもお金が %d円足りないみたいです。" ..
				"またいらしてください\n",
		success = "%s ですね。それでは %d円いただきます。\n",
		bye = "またどうぞ！",
	}
}

-- お店のやり取りを行う
function Shop()
	print("--------------------------------------------")
	-- ランダムで店員を選択
	local person = "default"
	math.randomseed(os.time())
	local rand = math.random()
	if rand < 0.5 then
		person = "woman"
	end
	local talk = talk_data[person]

	-- お店のやり取りを始める
	print(talk.welcome)
	while true do
		print(talk.select);
		local money = GetMoney();
		print(string.format("所持金：%d円", money))
		-- 商品リスト表示
		for i = 0, MAX_SHOP_ITEMS-1 do
			local name = GetItemName(i);
			local price = GetItemPrice(i);
			if price ~= -1 then
				print(string.format("%2d. %-10s, %6d円", i+1, name, price))
			end
		end
		print(" 0, 帰る")
		local num = GetSelection("どうする？")
		if (num == 0) then
			break
		end
		local is_success = false
		local name, price
		if num < 0 or num > MAX_SHOP_ITEMS or GetItemPrice(num -1) == -1 then
			print (talk.error)
		else
			-- 選択したアイテムの情報
			local index = num -1
			name = GetItemName(index);
			price = GetItemPrice(index);
			-- 所持金チェック
			if money < price then
				print(string.format(talk.nomoney, name, price - money))
			else
				is_success = true
			end
		end
		if is_success then
			-- 購入成功！
			print(string.format(talk.success, name, price))
			SetMoney(money - price)
		end
	end
	print(talk.bye)
	print("--------------------------------------------")
end
