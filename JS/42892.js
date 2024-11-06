class Tree {
	#myPosition
	#leftChild;
	#rightChild;
	constructor(position){
		this.#myPosition = position;
		this.#leftChild = null;
		this.#rightChild = null;
	}
	getMyPositionValue(){
		return this.#myPosition[1];
	}
	addChild(position, current, start, end){
		if(position[1][0] < current) {
			if (this.#leftChild !== null) {
				this.#leftChild.addChild(position, this.#leftChild.getMyPositionValue()[0], start, current);
				return;
			}
			this.#leftChild = new Tree(position);
			return;
		} else if (position[1][0] > current) {
			if (this.#rightChild !== null) {
				this.#rightChild.addChild(position, this.#rightChild.getMyPositionValue()[0], current, end);
				return;
			}
			this.#rightChild = new Tree(position);
			return;
		}
		throw new Error("중복된 값을 삽입하려고 합니다!");
	}
	traverse_preorder() {
		let leftChild = [];
		let rightChild = [];
		// 왼쪽 엘리먼트가 존재하는가?
		if ( this.#leftChild ) {
			leftChild = this.#leftChild.traverse_preorder();
		}
		
		// 오른쪽 엘리먼트가 존재하는가?
		if ( this.#rightChild ) {
			rightChild = this.#rightChild.traverse_preorder();
		}
		
		// 전위 탐색에 따라 currentItem 내 점으로 만든 배열 -> 좌측 Traverse 결과 배열 -> 우측 Traverse 결과 배열을 concat하여 배열을 반환
		return [].concat([this.#myPosition[0]], leftChild, rightChild);

	}
	
	traverse_postorder(treenode, currentHeightIdx, start, end) {
		let leftChild = [];
		let rightChild = [];
		// 왼쪽 엘리먼트가 존재하는가?
		if ( this.#leftChild ) {
			leftChild = this.#leftChild.traverse_postorder();
		}
		
		// 오른쪽 엘리먼트가 존재하는가?
		if ( this.#rightChild ) {
			rightChild = this.#rightChild.traverse_postorder();
		}
		
		// 전위 탐색에 따라 currentItem 내 점으로 만든 배열 -> 좌측 Traverse 결과 배열 -> 우측 Traverse 결과 배열을 concat하여 배열을 반환
		return [].concat(leftChild, rightChild, [this.#myPosition[0]]);
	}
}


function solution(nodeinfo) {
    var answer = [];
	
	// y좌표가 작을 수록, x좌표가 작을수록 앞으로 오도록 커스텀 오름차순 정렬
	nodeinfo = nodeinfo.reduce((prev, curr) => {
		const idx = prev.length+1;
		prev.push([idx, curr]);
		return prev;
	}, []).sort((a,b) => {
		if (a[1][1] === b[1][1]) return a[1][0] - b[1][0];
		return b[1][1] - a[1][1];
	});
	
	console.log(nodeinfo);
	
	const root = new Tree(nodeinfo[0]);
	for (let i = 1; i < nodeinfo.length; i++) {
		root.addChild(nodeinfo[i], nodeinfo[0][1][0], 0, 100001);
	}
	answer.push(root.traverse_preorder());
	answer.push(root.traverse_postorder());	
	
    return answer;
}