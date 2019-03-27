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
      console.log(this.$parent.form.departureDate)
      this.form.date = this.$parent.form.departureDate
      for (let i = 1; i < 60; i++) {
        this.options.push({value: i, label: i, children: [{value: 'A', label: 'A(靠窗)'}, {value: 'B', label: 'B'}, {value: 'C', label: 'C'}, {value: 'E', label: 'E'}, {value: 'F', label: 'F(靠窗)'}]})
      }
    },
    data () {
      return {
        dialogFormVisible: false,
        dialogData: 0,
        form: {
          date: '1999-01-01',
          seatClass: '1'
        },
        tableData: [{
          number: 'G1',
          departure: '北京南',
          arrival: '上海虹桥',
          departureTime: '9:00',
          arrivalTime: '13:28',
          cost: '04:28',
          businessClass: 100,
          firstClass: 100,
          secondClass: 100,
          prize: 10000
        }, {
          number: 'G5',
          departure: '北京南',
          arrival: '上海虹桥',
          departureTime: '7:00',
          arrivalTime: '13:08',
          cost: '05:48',
          businessClass: 100,
          firstClass: 10,
          secondClass: 100,
          prize: 10000
        }
        ],
        departureFilters: [{text: '北京南', value: '北京南'}, {text: '北京', value: '北京'}],
        arrivalFilters: [{text: '上海虹桥', value: '上海虹桥'}, {text: '上海', value: '上海'}],
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
