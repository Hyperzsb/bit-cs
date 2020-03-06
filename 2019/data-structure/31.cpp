#include<cstdio>
#include<cstdlib>
#include<vector>
using std::vector;
struct Post {
	int start;
	int end;
};
void AddPost(vector<Post> &post_list, Post new_post) {
	int size = post_list.size();
	int flag = 1;
	for (int i = 0; i < size; i++)
		if (post_list[i].end <= new_post.start || post_list[i].start >= new_post.end) {
			continue;
		} else if (post_list[i].start <= new_post.start && post_list[i].end >= new_post.end) {
			flag = 0;
			break;
		}	else {
			flag = 0;
			if (post_list[i].start <= new_post.start && post_list[i].end <= new_post.end) {
				new_post.start = post_list[i].end;
				AddPost(post_list, new_post);
			} else if (post_list[i].start >= new_post.start && post_list[i].end >= new_post.end) {
				new_post.end = post_list[i].start;
				AddPost(post_list, new_post);
			} else {
				Post new_post_a, new_post_b;
				new_post_a.start = new_post.start;
				new_post_a.end = post_list[i].start;
				new_post_b.start = post_list[i].end;
				new_post_b.end = new_post.end;
				AddPost(post_list, new_post_a);
				AddPost(post_list, new_post_b);
			}
		}
	if (flag)
		post_list.push_back(new_post);
}
int main() {
	int cal_num = 0;
	scanf("%d", &cal_num);
	while (cal_num--) {
		int post_num = 0, start = 0, end = 0, ans = 0;
		scanf("%d", &post_num);
		Post *post = (Post *)malloc(post_num * sizeof(Post));
		for (int i = 0; i < post_num; i++) {
			scanf("%d%d", &start, &end);
			post[i].start = start;
			post[i].end = end;
		}
		vector<Post> post_list;
		for (int i = post_num - 1; i >= 0; i--) {
			int original_size = post_list.size();
			AddPost(post_list, post[i]);
			if (post_list.size() > original_size)
				ans++;
		}
		printf("%d\n", ans);
	}

	return 0;
}
