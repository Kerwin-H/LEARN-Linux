class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) return{};
		vector<int> in;
		vector<vector<int>> out;
		queue<TreeNode*> q;
		q.push(root);
		int label = 0; 
		while (!q.empty()) {
			int cnt = q.size();
			label++; 
			while (cnt--) {
				TreeNode* node = q.front();
				in.push_back(node->val);
				q.pop();
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
			
			if (!(label & 1)) reverse(in.begin(), in.end());
			out.push_back(in);
			vector<int>().swap(in);
		}
		return out;
	}
};


class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) return{};
		vector<int> in;
		vector<vector<int>> out;
		
		deque<TreeNode*> q;
		q.push_front(root); 
		int label = 0; 
		while (!q.empty()) {
			int cnt = q.size();
			label++; 
			while (cnt--) {
				
				if (label & 1) {
					
					TreeNode* node = q.front();
					in.push_back(node->val);
					q.pop_front();
					if (node->left) q.push_back(node->left);
					if (node->right) q.push_back(node->right);
				}
				else {
					
					TreeNode* node = q.back();
					in.push_back(node->val);
					q.pop_back();
					if (node->right) q.push_front(node->right);
					if (node->left) q.push_front(node->left);
				}
			}
			
			out.push_back(in);
			vector<int>().swap(in);
		}
		return out;
	}
};
