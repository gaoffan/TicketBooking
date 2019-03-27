<template>
<div>
  <div class="topbar block">
  <el-button circle icon="el-icon-back" @click="onBack"></el-button>
     共找到 {{ tableData.length }} 项结果。
     <el-date-picker style="float:right" v-model="form.date" align="right" type="date"></el-date-picker>
  </div>
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
      prop="departure"
      label="出发站"
      width="90"
      :filters="departureFilters"
      :filter-method="filterHandler">
    </el-table-column>
    <el-table-column
      prop="arrival"
      label="到达站"
      width="90"
      :filters="arrivalFilters"
      :filter-method="filterHandler">
    </el-table-column>
    <el-table-column
      sortable
      prop="departureTime"
      label="出发时间"
      width="120">
    </el-table-column>
    <el-table-column
      sortable
      prop="arrivalTime"
      label="到达时间"
      width="120">
    </el-table-column>
    <el-table-column
      sortable
      prop="cost"
      label="历时"
      width="90">
    </el-table-column>
    <el-table-column
      prop="businessClass"
      label="商务座"
      width="90">
    </el-table-column>
    <el-table-column
      prop="firstClass"
      label="一等座"
      width="90">
    </el-table-column>
    <el-table-column
      prop="secondClass"
      label="二等座"
      width="90">
    </el-table-column>
    <el-table-column
      fixed="right"
      label="操作"
      width="120">
      <template slot-scope="scope">
        <el-button type="primary" size="mini" @click="onSubmit(scope.$index)">预定</el-button>
      </template>
    </el-table-column>
  </el-table>
  <el-dialog title="预定车票" :visible.sync="dialogFormVisible" width="600px">
    <div style="text-align:center">
    <h1>{{tableData[dialogData].number}} {{tableData[dialogData].departure}} -- {{tableData[dialogData].arrival}} {{tableData[dialogData].departureTime}} 
      <red>        ¥{{tableData[dialogData].prize}}</red></h1>
    </div>
    <el-form :model="form" label-width="80px"> 
    <el-form-item label="席位等级">
    <el-radio v-model="form.seatClass" label="1" border size="medium">商务座</el-radio>
    <el-radio v-model="form.seatClass" label="2" border size="medium">一等座</el-radio>
    <el-radio v-model="form.seatClass" label="3" border size="medium">二等座</el-radio>
    </el-form-item>
    <el-form-item label="选座">
    <el-cascader expand-trigger="hover" :options="options" v-model="selectedOptions2" @change="handleChange">
  </el-cascader>
  </el-form-item>
    </el-form>    
  <span slot="footer" class="dialog-footer">
  <el-button type="primary" @click="onSubmit(dialogData)">确定</el-button>
  <el-button @click="dialogFormVisible = false">取消</el-button>
  </span>
</el-dialog>
</div>
</template>


<script>
  export default {
    name: 'SearchResult',
    methods: {
      onBack () {
        this.$emit('onback')
      },
      onSubmit (index) {
        this.dialogFormVisible = true
        this.dialogData = index
      },
      deleteRow (index, rows) {
        rows.splice(index, 1)
      },
      resetDateFilter () {
        this.$refs.filterTable.clearFilter('date')
      },
      clearFilter () {
        this.$refs.filterTable.clearFilter()
      },
      formatter (row, column) {
        return row.address
      },
      filterTag (value, row) {
        return row.tag === value
      },
      filterHandler (value, row, column) {
        const property = column['property']
        return row[property] === value
      },
      handleChange (value) {
        console.log(value)
      }
    },
    created () {
      let fs = require('fs')
      console.log(this.$parent.form.departureDate)
      this.form.date = this.$parent.form.departureDate
      for (let i = 1; i < 60; i++) {
        this.options.push({value: i, label: i, children: [{value: 'A', label: 'A(靠窗)'}, {value: 'B', label: 'B'}, {value: 'C', label: 'C'}, {value: 'E', label: 'E'}, {value: 'F', label: 'F(靠窗)'}]})
      }
      const { ipcRenderer } = require('electron')
      ipcRenderer.send('get-app-path')
      ipcRenderer.on('got-app-path', (event, path) => {
        this.path = path
        fs.readFile(path + '/lines.json', (err, data) => {
          if (!err) {
            let lines = JSON.parse(data)
            console.log(lines)
            for (let item of lines) {
              console.log(item.stations)
              console.log(this.$parent.form.departure)
              for (let s = 0; s < item.stations.length - 1; s++) {
                if (item.stations[s].name.indexOf(this.$parent.form.departure) === 0) {
                  console.log(s + '' + item.stations[s].name)
                  for (let i = s; i < item.stations.length; i++) {
                    if (item.stations[i].name.indexOf(this.$parent.form.arrival) === 0) {
                      let time1 = item.stations[s].time.split(':')
                      let time2 = item.stations[i].time.split(':')
                      let costmin = (parseInt(time2[0]) * 60 + parseInt(time2[1])) - (parseInt(time1[0]) * 60 + parseInt(time1[1]))
                      let hour = costmin / 60
                      let mins = costmin % 60
                      let str = hour.toString() + ':' + mins.toString()
                      this.tableData.push({
                        number: item.number,
                        departure: item.stations[s].name,
                        arrival: item.stations[i].name,
                        departureTime: item.stations[s].time,
                        arrivalTime: item.stations[i].time,
                        cost: str,
                        businessClass: item.businessClass,
                        firstClass: item.firstClass,
                        secondClass: item.secondClass,
                        prize: item.stations[i].prize - item.stations[s].prize
                      })
                      break
                    }
                  }
                }
              }
            }
            let dep = []
            let arr = []
            for (let item of this.tableData) {
              if (!dep.includes(item.departure)) {
                dep.push(item.departure)
                this.departureFilters.push({text: item.departure, value: item.departure})
              }
              if (!arr.includes(item.arrival)) {
                arr.push(item.arrival)
                this.arrivalFilters.push({text: item.arrival, value: item.arrival})
              }
            }
            // this.tableData = lines
            // this.$message({message: '读取完毕!', type: 'success', showClose: true})
          } else {
            this.$message({message: err, type: 'warning', showClose: true})
          }
        })
      })
    },
    data () {
      return {
        dialogFormVisible: false,
        dialogData: 0,
        form: {
          date: '1999-01-01',
          seatClass: '1',
          departure: '',
          arrival: '',
          prize: ''
        },
        tableData: [],
        departureFilters: [],
        arrivalFilters: [],
        options: [],
        selectedOptions: [],
        selectedOptions2: []
      }
    }
  }
</script>

<style>
.topbar {
  color: #303133;
  margin-bottom: 1rem;
  margin-right: 1rem;
}
red{
  color:red;
}
</style>
