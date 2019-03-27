<template>
<div>
<el-table
    :data="tableData"
    border
    style="width: 100%">
    <el-table-column
      fixed
      sortable
      prop="number"
      label="车次"
      width="80">
    </el-table-column>
    <el-table-column
      prop="pass"
      label="途径">
      <template slot-scope="scope">
        <el-tag class="tag" type="success" v-for="(item,index) in scope.row.pass" :key="index" size="medium">{{ scope.row.pass[index].name }}</el-tag>
      </template>
    </el-table-column>
    <el-table-column
      prop="businessClass"
      label="商务座"
      width="80">
    </el-table-column>
    <el-table-column
      prop="firstClass"
      label="一等座"
      width="80">
    </el-table-column>
    <el-table-column
      prop="secondClass"
      label="二等座"
      width="80">
    </el-table-column>
    <el-table-column
      label="操作"
      width="80">
      <template slot-scope="scope">
        <el-button type="danger" size="mini" @click="onSubmit(scope.$index)">删除</el-button>
      </template>
    </el-table-column>
  </el-table>
</div>
</template>

<script>
  export default {
    name: 'line-manager',
    data () {
      return {
        tableData: [{
          number: 'G1',
          pass: [{name: '北京西', time: '9:00', prize: '0'}, {name: '济南北', time: '10:00', prize: '200'}, {name: '上海虹桥', time: '13:00', prize: '1000'}],
          businessClass: 100,
          firstClass: 100,
          secondClass: 100
        }]
      }
    }
  }
</script>

<style>

.container {
    position: relative;
    top: 0;
    bottom: 0;
    width: 100%;
}
.header {
    text-align: center;
    padding: 0;
}
.main {
  padding: 10px;
}
.tag {
  margin-right: 0.2rem 
}
</style>
