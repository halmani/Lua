-- チームリスト、試合リストから計算
function sumresult(teamlist, matchlist)
	local name, prop, team, match
	local a, b, ascore, bscore, one
	local result = {}	-- チーうの成績一覧

	for idx = 1, #teamlist do
		team = teamlist[idx]
		-- チームの成績テーブルをセット
		name = team.name
		prop = { point=0, win=0, even=0, lose=0, get=0, loss=0 }
		result[name] = prop	-- 成績一覧に登録
		team.result = prop
	end
	-- 1つの試合結果を1チーム成績にセット
	function setresult(res, ascore, bscore)
		if (ascore > bscore) then
			res.point = res.point + 3
			res.win = res.win + 1
		elseif (ascore == bscore) then	-- 引き分け
			res.point = res.point + 1
			res.even = res.even + 1
		else
			res.lose = res.lose + 1
		end
		res.get = res.get + ascore		-- ゴール数の合計
		res.loss = res.loss + bscore	-- 失点の合計
	end
	-- すべての対戦結果を修正
	for idx = 1, #matchlist do
		match = matchlist[idx]
		a = match[1]
		b = match[2]
		ascore = match.score[1]
		bscore = match.score[2]
		-- 1試合につき、両チームの成績を更新
		setresult(result[a], ascore, bscore)
		setresult(result[b], bscore, ascore)
	end
	-- 勝ち点での比較関数
	function sortbypoint(a, b)
		if (a.result.point > b.result.point) then
			return 1
		end
	end

	table.sort(teamlist, sortbypoint)	-- チームの順位並べ替え
	-- 集計結果の出力
	print("------------------------------------------------")
	print(" team       point   win/even/lose/ get/lost/diff")
	print("------------------------------------------------")
	for idx = 1, #teamlist do
		one = teamlist[idx].result
		name = teamlist[idx].name
		print(string.format(
			"%-11s %3d    %3d %3d  %3d   %3d %3d %+3d",
			name, one.point, one.win, one.even, one.lose,
			one.get, one.loss, one.get-one.loss
		))
	end
	print("------------------------------------------------")
end

-- データを読み込み、集計する
dofile("data1.lua")
sumresult(teamlist, matchlist)
