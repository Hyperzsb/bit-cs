#include <cstdio>
#include <cmath>
#include <algorithm>

struct PointX {
    int index;
    double x_position;
    double y_position;
};

struct PointY {
    int index;
    double x_position;
    double y_position;
};

PointX point_list[100000];

bool CompareX(PointX a, PointX b) {
    return a.x_position < b.x_position;
}

bool CompareY(PointY a, PointY b) {
    return a.y_position < b.y_position;
}

double Distance(PointX a, PointX b) {
    return sqrt((a.x_position - b.x_position) * (a.x_position - b.x_position) +
                (a.y_position - b.y_position) * (a.y_position - b.y_position));
}

double Distance(PointY a, PointY b) {
    return sqrt((a.x_position - b.x_position) * (a.x_position - b.x_position) +
                (a.y_position - b.y_position) * (a.y_position - b.y_position));
}

void ResetPointList(PointY *source_list, PointY *destination_list, int start, int middle, int end) {
    int index = start, left_index = start, right_index = middle + 1;
    while (index <= end && left_index <= middle && right_index <= end)
        if (source_list[left_index].y_position < source_list[right_index].y_position)
            destination_list[index++] = source_list[left_index++];
        else
            destination_list[index++] = source_list[right_index++];
    while (left_index <= middle)
        destination_list[index++] = source_list[left_index++];
    while (right_index <= end)
        destination_list[index++] = source_list[right_index++];
}

double Find(PointX *point_x_list, PointY *point_y_list, PointY *tmp_point_y_list, int start, int end) {
    if (end - start == 1) {
        return Distance(point_x_list[start], point_x_list[start + 1]);
    } else if (end - start == 2) {
        double distance_1 = Distance(point_x_list[start], point_x_list[start + 1]),
                distance_2 = Distance(point_x_list[start], point_x_list[start + 2]),
                distance_3 = Distance(point_x_list[start + 1], point_x_list[start + 2]);
        if (distance_1 < distance_2) {
            if (distance_1 < distance_3)
                return distance_1;
            else
                return distance_3;
        } else {
            if (distance_2 < distance_3)
                return distance_2;
            else
                return distance_3;
        }
    } else {
        int middle = (start + end) / 2, left_index = start, right_index = middle + 1, middle_index = start;
        for (int i = start; i <= end; i++)
            if (point_y_list[i].index <= middle)
                tmp_point_y_list[left_index++] = point_y_list[i];
            else
                tmp_point_y_list[right_index++] = point_y_list[i];
        double left_minimum_distance = Find(point_x_list, tmp_point_y_list, point_y_list, start, middle),
                right_minimum_distance = Find(point_x_list, tmp_point_y_list, point_y_list, middle + 1, end),
                minimum_distance =
                left_minimum_distance < right_minimum_distance ? left_minimum_distance : right_minimum_distance;
        ResetPointList(tmp_point_y_list, point_y_list, start, middle, end);
        for (int i = start; i <= end; i++)
            if (std::abs(point_x_list[middle].x_position - point_y_list[i].x_position) < minimum_distance)
                tmp_point_y_list[middle_index++] = point_y_list[i];
        for (int i = start; i < middle_index; i++)
            for (int j = i + 1;
                 j < middle_index &&
                 (tmp_point_y_list[j].y_position - tmp_point_y_list[i].y_position < minimum_distance);
                 j++) {
                double distance = Distance(tmp_point_y_list[i], tmp_point_y_list[j]);
                if (distance < minimum_distance)
                    minimum_distance = distance;
            }
        return minimum_distance;
    }
}

double FindMinimumDistance(PointX *point_x_list, int point_num) {
    std::sort(point_x_list, point_x_list + point_num, CompareX);
    PointY *point_y_list = new PointY[point_num + 5],
            *tmp_point_y_list = new PointY[point_num + 5];
    for (int i = 0; i < point_num; i++) {
        point_y_list[i].index = point_x_list[i].index;
        point_y_list[i].x_position = point_x_list[i].x_position;
        point_y_list[i].y_position = point_x_list[i].y_position;
    }
    std::sort(point_y_list, point_y_list + point_num, CompareY);
    double minimum_distance = Find(point_x_list, point_y_list, tmp_point_y_list, 0, point_num - 1);
    delete[] point_y_list;
    delete[] tmp_point_y_list;
    return minimum_distance;
}

int main() {
    int point_num = 0;
    scanf("%d", &point_num);
    while (point_num != 0) {
        for (int i = 0; i < point_num; i++)
            scanf("%lf%lf", &point_list[i].x_position, &point_list[i].y_position);
        double minimum_distance = FindMinimumDistance(point_list, point_num);
        printf("%.2lf\n", minimum_distance / 2);
        scanf("%d", &point_num);
    }
    return 0;
}