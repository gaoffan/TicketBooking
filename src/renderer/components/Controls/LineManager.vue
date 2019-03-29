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
      prop="stations"
      label="途径">
      <template slot-scope="scope">
        <el-tag class="tag" type="success" v-for="(item,index) in scope.row.stations" :key="index" size="medium">{{ scope.row.stations[index].name }}</el-tag>
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
  let fs = require('fs')
  export default {
    name: 'line-manager',
    methods: {
      onSubmit (index) {
        this.tableData.splice(index, 1)
        console.log(this.tableData)
        fs.writeFile(this.path + '/lines.json', JSON.stringify(this.tableData), (err) => {
          if (!err) {
            this.$message({message: '删除成功!', type: 'success', showClose: true})
          } else {
            this.$message({message: err, type: 'warning', showClose: true})
          }
        })
      }
    },
    created () {
      const { ipcRenderer } = require('electron')
      ipcRenderer.send('get-app-path')
      ipcRenderer.on('got-app-path', (event, path) => {
        this.path = path
        fs.readFile(path + '/lines.json', (err, data) => {
          if (!err) {
            let lines = JSON.parse(data)
            this.tableData = lines
          }
        })
      })
    },
    data () {
      return {
        path: '',
        tableData: []
      }
    }
  }
</script>

<style>
.tag {
  margin-right: 0.2rem 
}
</style>
